

#include <boost/program_options.hpp>

#include <vrj/Kernel/Kernel.h>
#include <vrj/vrjParam.h>

namespace
{
    typedef std::vector<std::string> string_list_type;

    string_list_type vrj_config_files;

    void
    eval_cmdline(boost::program_options::variables_map &var_map, char argv0[])
    {
        if(var_map.count("vrj-config-file"))
        {
            std::cerr << "\nvrj config files are:\n";

            string_list_type::const_iterator current(vrj_config_files.begin());

            while(current != vrj_config_files.end())
            {
                std::cerr << "\t"
                          << *current
                          << '\n';

                vrj::Kernel::instance()->loadConfigFile(*current);

                ++current;
            }

            std::cerr << std::endl;
        }
    }

    void process_cmdline(int argc, char* argv[])
    {
        namespace po = boost::program_options;

        po::options_description  generic("Generic Options");
        po::options_description  common("Command-Line Options");

        generic.add_options()
            ("help,h",
             // nor args
             "display this help message");

        common.add_options()
            ("vrj-config-file",
             po::value(&vrj_config_files)->composing(),
             "configuration file for VRJuggler");

        // command line handles all options
        po::options_description cmd_line;

        cmd_line.add(generic);
        cmd_line.add(common);

        po::positional_options_description positionals;

        positionals.add("vrj-config-file", -1);  // positional args are config files

        // description used to print the usage message - does not show hidden opts
        po::options_description visible;

        visible.add(generic);
        visible.add(common);

        {
#if (__VJ_version >= 2003000)
            vrj::Kernel* kernel(vrj::Kernel::instance());

            // visible.add(kernel->getGeneralOptions());
            visible .add(kernel->getClusterOptions());
            cmd_line.add(kernel->getClusterOptions());
            // visible.add(kernel->getConfigOptions());
#endif
        }

        // parse commandline
        bool              print_help(false);
        po::variables_map var_map;
        signed            return_value(EXIT_SUCCESS);

        try
        {
            po::store(po::command_line_parser(argc, argv).options(cmd_line).positional(positionals).run(),
                      var_map);
            po::notify(var_map);
        }

        catch(std::exception const& ex)
        {
            std::cerr << '\n' << basename(argv[0]) << ' ' << ex.what() << std::endl;

            print_help   = true;
            return_value = EXIT_FAILURE;
        }

        if (var_map.count("help") || print_help) {
            std::cerr << '\n'
                      << basename(argv[0])
                      << " [OPTIONS] [vrj-config-file.jconf ...]\n"
                      << visible
                      << std::endl;

            std::exit(return_value);
        }

#if (__VJ_version >= 2003000)
        {
            try
            {
                vrj::Kernel::instance()->init(var_map);
            }
            catch(boost::bad_any_cast const&)
            {
                ; // just sink
            }
        }
#endif

        eval_cmdline(var_map, argv[0]);
    }

} // namespace {


int
main(int argc, char* argv[])
{
    process_cmdline(argc, argv);

    { // keep this block together
        vrj::Kernel* kernel(vrj::Kernel::instance());

        // CAUTION|BUG: vrj::Kernel::start() claims to return 0 on success
        if(!kernel->start())
        {
            std::cerr << "\n\n"
                      << basename(argv[0])
                      << "error: unable to start VRJuggler kernel loop; exiting"
                      << std::endl;

            std::exit(EXIT_FAILURE);
        }

        kernel->waitForKernelStop();
    }

    return EXIT_SUCCESS;
}

