#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

void show_help() {
    std::cout << R"(
aptx 2.4.5 (wrapper)
Usage: aptx [options] command

apt is a commandline package manager and provides commands for
searching and managing as well as querying information about packages.
It provides the same functionality as the specialized APT tools,
like apt-get and apt-cache, but enables options more suitable for
interactive use by default.

Most used commands:
  file - Install Local .deb
  list - list packages based on package names
  search - search in package descriptions
  show - show package details
  install - install packages
  reinstall - reinstall packages
  remove - remove packages
  autoremove - Remove automatically all unused packages
  update - update list of available packages
  upgrade - upgrade the system by installing/upgrading packages
  full-upgrade - upgrade the system by removing/installing/upgrading packages
  edit-sources - edit the source information file
  satisfy - satisfy dependency strings

See apt(8) for more information about the available commands.
Configuration options and syntax is detailed in apt.conf(5).
Information about how to configure sources can be found in sources.list(5).
Package and version choices can be expressed via apt_preferences(5).
Security details are available in apt-secure(8).
                                        This APT has Super Cow Powers.
)";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "No command provided. Run 'aptx help' for usage information." << std::endl;
        return 1;
    }

    std::string cmd(argv[1]);

    if (cmd.substr(0, 1) == "f") {
        std::vector<std::string> args(argv + 2, argv + argc);
        for (const auto& arg : args) {
            system(("dpkg -L " + arg).c_str());
        }
    } else if (cmd.substr(0, 1) == "h") {
        show_help();
    } else if (cmd.substr(0, 2) == "sh" || cmd.substr(0, 3) == "inf") {
        system(("apt show " + cmd.substr(2)).c_str());
    } else if (cmd.substr(0, 3) == "add" || cmd.substr(0, 1) == "i") {
        system(("apt install " + cmd.substr(3)).c_str());
    } else if (cmd.substr(0, 5) == "autoc") {
        system("apt autoclean");
    } else if (cmd.substr(0, 2) == "cl") {
        system("apt clean");
    } else if (cmd.substr(0, 5) == "list-a") {
        system(("apt list " + cmd.substr(6)).c_str());
    } else if (cmd.substr(0, 5) == "list-i") {
        system(("apt list --installed " + cmd.substr(7)).c_str());
    } else if (cmd.substr(0, 3) == "rei") {
        system(("apt install --reinstall " + cmd.substr(4)).c_str());
    } else if (cmd.substr(0, 2) == "se") {
        system(("apt search " + cmd.substr(2)).c_str());
    } else if (cmd.substr(0, 2) == "un" || cmd.substr(0, 4) == "rem" || cmd.substr(0, 2) == "rm" || cmd.substr(0, 3) == "del") {
        system(("apt remove " + cmd.substr(3)).c_str());
    } else if (cmd.substr(0, 2) == "up") {
        system("apt update");
        system(("apt full-upgrade " + cmd.substr(3)).c_str());
    } else {
        std::cerr << "Unknown command: '" << cmd << "' (run 'aptx help' for usage information)" << std::endl;
        return 1;
    }

    return 0;
}