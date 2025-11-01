#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

static int open_serial(const std::string& dev, speed_t baud=B115200) {
    int fd = ::open(dev.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd < 0) { perror("open"); return -1; }

    // Prendi impostazioni correnti
    termios tio{};
    if (tcgetattr(fd, &tio) < 0) { perror("tcgetattr"); ::close(fd); return -1; }

    // Modalità raw, 8N1, no flow control
    cfmakeraw(&tio);
    tio.c_cflag &= ~(PARENB | CSTOPB | CRTSCTS);
    tio.c_cflag |= (CLOCAL | CREAD);        // abilita ricezione

    // Baud
    cfsetispeed(&tio, baud);
    cfsetospeed(&tio, baud);

    // Timeout non bloccante per write/read (qui non leggiamo, ma ok)
    tio.c_cc[VMIN]  = 0;
    tio.c_cc[VTIME] = 1; // 0.1 s

    if (tcsetattr(fd, TCSANOW, &tio) < 0) { perror("tcsetattr"); ::close(fd); return -1; }

    // Pulisci buffer
    tcflush(fd, TCIOFLUSH);
    return fd;
}

static uint8_t checksum(uint8_t len, uint8_t cmd, int8_t delta) {
    uint16_t s = (uint16_t)len + (uint16_t)cmd + (uint16_t)(uint8_t)delta;
    return (uint8_t)(s & 0xFF);
}

static bool send_delta(int fd, int8_t delta) {
    const uint8_t SOF1=0xAA, SOF2=0x55;
    const uint8_t LEN = 0x02;
    const uint8_t CMD = 0x10;

    uint8_t crc = checksum(LEN, CMD, delta);

    uint8_t frame[6] = {SOF1, SOF2, LEN, CMD, (uint8_t)delta, crc};

    // Scrivi in modo sincrono
    ssize_t n = ::write(fd, frame, sizeof(frame));
    if (n != (ssize_t)sizeof(frame)) {
        perror("write");
        return false;
    }
    // (facoltativo) attesa svuotamento
    tcdrain(fd);

    // Log esadecimale
    std::cout << "TX:";
    for (auto b : frame) std::printf(" %02X", b);
    std::cout << "  (delta=" << (int)delta << ")\n";
    return true;
}

int main(int argc, char** argv) {
    std::string dev = "/dev/ttyUSB0";
    if (argc > 1) dev = argv[1];

    int fd = open_serial(dev, B115200);
    if (fd < 0) {
        std::cerr << "Errore apertura seriale su " << dev << "\n";
        return 1;
    }
    std::cout << "Seriale aperta su " << dev << " @115200 8N1\n";
    std::cout << "Digita 'q' per uscire.\n\n";

    while (true) {
        std::string dir;
        std::cout << "In quale direzione vuoi spostare il servo? (dx/sx): ";
        if (!std::getline(std::cin, dir)) break;
        if (dir == "q" || dir == "Q") break;

        // normalizza
        for (auto& c : dir) c = std::tolower((unsigned char)c);
        if (dir != "dx" && dir != "sx") {
            std::cout << "Inserisci 'dx' o 'sx'.\n";
            continue;
        }

        std::string valStr;
        std::cout << "Di quanto vuoi muovere il servo (gradi 1..90)? ";
        if (!std::getline(std::cin, valStr)) break;
        if (valStr == "q" || valStr == "Q") break;

        int v = 0;
        try { v = std::stoi(valStr); } catch (...) { v = 0; }
        if (v < 1) v = 1;
        if (v > 90) v = 90;

        int8_t delta = (dir == "dx") ? (int8_t)(+v) : (int8_t)(-v);

        if (!send_delta(fd, delta)) {
            std::cerr << "Invio fallito.\n";
        }
    }

    ::close(fd);
    return 0;
}
