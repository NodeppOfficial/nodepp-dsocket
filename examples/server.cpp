#include <nodepp/nodepp.h>
#include <hsocket/hs.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain() {

    auto cin    = fs::std_input();
    auto server = hs::server();

    server.onConnect([=]( hs_t cli ){

        cli.onClose([=](){ process::exit(); });

        cin.onData([=]( string_t data ){
            cli.write( data );
        });

        cli.onData([=]( string_t data ){
            console::log( data );
        });

        console::log("Connected");

    });

    server.listen( "localhost", 8000, [=](...){
        console::log( "-> http://localhost:8000" );
    });
    
    stream::pipe( cin );
    
}