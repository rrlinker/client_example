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

int main() {
    // dolzna bitj vozmoznostj request nestkolko libraryj za 1 sessiju
    //
    // dolzna bitj vozmoznostj request library v drugoj process
    // => Linker class -- abstract;
    // LocalLinker
    // RemoteLinker
    //
    // class Library
    // map<symbol, address>
    // call(symbol, params...);
    //
    // Library class -- abstract;
    // LocalLibrary
    // RemoteLibrary
    //
    // dolzna bitj vozmoznostj zashifrovatj connection => Connection class -- abstract.
    
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

        rrl::LocalLibrary library("test");
        rrl::LocalLinker linker;

        rrl::Librarian librarian(courier);
        librarian.link(linker, library);

        conn.disconnect();

        conn.cleanup();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    getchar();

    return 0;
}
