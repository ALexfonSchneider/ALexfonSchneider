#include <iostream>
#include <filesystem>
#include <QCoreApplication>
#include <QProcess>
#include <QThread>

namespace fs = std::filesystem;

void SortingFunc(char*);
bool isDerictoryExist(const fs::path &); // return true if derectory exists

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(argc == 1) {
        QProcess process;
        process.start("SortingProgram.exe"); //Оба исполняющих файла собираются в одной директории.
        process.waitForFinished();
    }
    else if(argc == 2) {
        SortingFunc(argv[1]);
    }
    else {
        std::cout << "too many argements, needs one or two.\n" << std::endl;
    }
}

void SortingFunc(char* argv) {
    fs::path primalDirectoryPath = argv;
    fs::directory_iterator* primalFilesDerictoryIterator = new fs::directory_iterator(primalDirectoryPath);
    if(primalDirectoryPath == "") {
        std::cout << "You need to select a directory for sorting" << std::endl;
        delete primalFilesDerictoryIterator;
        return;
    }
    if(primalDirectoryPath == "" || primalDirectoryPath == "C://" || primalDirectoryPath == "C:\\" || primalDirectoryPath == "C:/Program Files"
            ||  primalDirectoryPath == "C://Program Files" || primalDirectoryPath == "C:\\Program Files" || primalDirectoryPath == "C://Program Files (x86)") {
        std::cout << "You can't sort system directories" << std::endl;
        delete primalFilesDerictoryIterator;
        return;
    }
    for (const auto& FILE : *primalFilesDerictoryIterator) {
        if (FILE.status().type() == fs::file_type::directory) {
            std::string MyFolderName = "Folders";
            if (FILE.path().filename().string() != MyFolderName) {
                if (((FILE.path().filename().string().at(0) == '.') && (FILE.path().extension().string() == "")) == false) {
                    if (isDerictoryExist(primalDirectoryPath.string() + "/" + MyFolderName) == false)
                        fs::create_directory(primalDirectoryPath.string() + "/" + MyFolderName); // Если сортировачная папка не созданна -создаем ее.
                    if (isDerictoryExist(primalDirectoryPath.string() + "/" + MyFolderName + "/" + FILE.path().filename().string()) == false) {
                        fs::create_directory(primalDirectoryPath.string() + "/" + MyFolderName + "/" + FILE.path().filename().string());
                        std::cout << FILE.path() << " -> " << primalDirectoryPath.string() + "/" + MyFolderName + "/" + FILE.path().filename().string() << std::endl;
                        fs::copy(FILE, primalDirectoryPath.string() + "/" + MyFolderName + "/" + FILE.path().filename().string(), fs::copy_options::recursive | fs::copy_options::skip_existing);
                        fs::remove_all(FILE);
                    }
                }
            }
        }
        else { // сортировка не директорий
            if (isDerictoryExist(primalDirectoryPath.string() + "/" + (FILE.path().extension().string())) == false) // Если сортировачная папка не созданна - создаем ее.
                fs::create_directory(primalDirectoryPath.string() + "/" + FILE.path().extension().string());
            std::cout << FILE.path() << " -> " << primalDirectoryPath.string() + "/" + FILE.path().extension().string() << std::endl;
            fs::copy(FILE, primalDirectoryPath.string() + "/" + FILE.path().extension().string(), fs::copy_options::skip_existing);
            fs::remove(FILE);
        }
    }
    delete primalFilesDerictoryIterator;
}

bool isDerictoryExist(const fs::path &path) {
    return fs::exists(path);
}
