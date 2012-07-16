#ifndef _BROKER_APPLICATION_H_
#define _BROKER_APPLICATION_H_

#include "broker_service.h"
#include "net_factory.h"
#include "utility/arg_helper.h"

namespace ff {

class broker_application_t
{
public:
    struct app_info_t
    {
        app_info_t():acceptor(NULL)
        {}
        broker_service_t broker_service;
        acceptor_i*      acceptor;
    };
    static int run(int argc, char** argv)
    {
        arg_helper_t arg(argc, argv);

        if (arg.get_option_value("-l").empty())
        {
            cout <<"-l arg need \n";
            exit(-1);
        }

        net_factory_t::start(1);

        singleton_t<app_info_t>::instance().acceptor = net_factory_t::listen(arg.get_option_value("-l"), &(singleton_t<app_info_t>::instance().broker_service));

        assert(singleton_t<app_info_t>::instance().acceptor && "can not listen this address");
        return 0;
    }
};

}
#endif
