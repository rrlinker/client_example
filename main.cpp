#include <ws_connection.h>
#include <courier.h>
#include <linker.h>
#include <authorizer.h>
#include <locallibrary.h>
#include <remotelibrary.h>
#include <locallinker.h>
#include <remotelinker.h>
#include <librarian.h>

#include <iostream>
#include <conio.h>

int main() {
    try {
        rrl::win::WSConnection conn;
        conn.startup();

        std::array<uint8_t, 16> ip = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 127, 0, 0, 1 };
        uint16_t port = 40545;
        rrl::Address addr(ip, port);
        conn.connect(addr);
        rrl::Courier courier(conn);

        // OPTIONAL
        rrl::Token token = {};
        rrl::Authorizer authorizer(token);
        authorizer.authorize(courier);

        rrl::LocalLibrary libmsgbox("msgbox");
        rrl::LocalLinker linker;

        rrl::Librarian librarian(courier);
        librarian.link(linker, libmsgbox);

        if (libmsgbox["AskBox"].ccall<int>("Yes, or no?") == IDYES) {
            rrl::LocalLibrary libtest("test");
            librarian.link(linker, libtest);
            libtest["rrl_main"].ccall<DWORD>(0);
            librarian.unlink(linker, libtest);
        }
        librarian.unlink(linker, libmsgbox);

        conn.disconnect();

        conn.cleanup();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "Press any key to exit ... " << std::endl;
    getch();

    return 0;
}
