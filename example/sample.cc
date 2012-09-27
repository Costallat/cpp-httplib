//
//  sample.cc
//
//  Copyright (c) 2012 Yuji Hirose. All rights reserved.
//  The Boost Software License 1.0
//

#include <httpsvrkit.h>
#include <cstdio>
#include <signal.h>

using namespace httpsvrkit;

template<typename Fn> void signal(int sig, Fn fn)
{
    static std::function<void ()> signal_handler_;
    struct SignalHandler { static void fn(int sig) { signal_handler_(); } };
    signal_handler_ = fn;
    signal(sig, SignalHandler::fn);
}

int main(void)
{
    const char* hi = "/hi";
    HTTP_SERVER("localhost", 1234) {
        // svr, req, res

        GET("/", {
            res.set_redirect(hi);
        });

        GET("/hi", {
            res.set_content("Hello World!");
        });

        GET("/dump", {
            res.set_content(dump_request(cxt));
        });

        signal(SIGINT, [&](){
            svr->stop();
        });
    }
}

// vim: et ts=4 sw=4 cin cino={1s ff=unix