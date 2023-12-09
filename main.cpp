#include <rrlinker/com/raw_courier.hpp>
#include <rrlinker/client/linker.hpp>
#include <rrlinker/client/locallibrary.hpp>
#include <rrlinker/client/locallinker.hpp>
#include <rrlinker/client/librarian.hpp>
#include <rrlinker/client/ws_connection.hpp>

#include <iostream>
#include <conio.h>

int main() {
    try {
        rrl::win::WSConnection conn;
        conn.startup();

        std::array<uint8_t, 16> ip{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 127, 0, 0, 1 };
        uint16_t port = 40545;
        rrl::Address addr({ ip, port });
        conn.connect(addr);
        rrl::RawCourier courier(conn);

        rrl::LocalLibrary lib("example");
        rrl::LocalLinker linker;

        rrl::Librarian librarian(courier);
        librarian.link(linker, lib);

        int result = lib["example"].ccall<int>();
        librarian.unlink(linker, lib);

        conn.disconnect();

        conn.cleanup();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "Press any key to exit ... " << std::endl;
    getch();

    return 0;
}
