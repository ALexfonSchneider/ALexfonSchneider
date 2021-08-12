#include "sortingclass.h"
#include "ui_sortingclass.h"

SortingClass::SortingClass(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SortingClass)
{
    ui->setupUi(this);
}

SortingClass::~SortingClass()
{
    delete ui;
}

bool isDerictoryExist(const fs::path &path) {
        return fs::exists(path);
}

void SortingClass::on_pushButton_clicked()
{
    str_primalDirectoryPath = ui->lineEdit->text();
    fs::path primalDirectoryPath = str_primalDirectoryPath.toStdString();
    if(str_primalDirectoryPath == "") {
        ui->textEdit->insertPlainText("Select Directory for sorting \n");
        return;
    }
    if(primalDirectoryPath == "" || primalDirectoryPath == "C://" || primalDirectoryPath == "C:\\" || primalDirectoryPath == "C:/Program Files"
            ||  primalDirectoryPath == "C://Program Files" || primalDirectoryPath == "C:\\Program Files" || primalDirectoryPath == "C://Program Files (x86)") {
        ui->textEdit->insertPlainText("You can't sort system directories\n");
        return;
    }
    primalDirectoryPath.make_preferred();
    fs::directory_iterator* primalFilesDerictoryIterator = new fs::directory_iterator(primalDirectoryPath);
    for (const auto& FILE : *primalFilesDerictoryIterator) {
        if (FILE.is_directory()) {
             std::string MyFolderName = "Folders";
             if (FILE.path().filename() != MyFolderName) {
                 if (((FILE.path().filename().string().at(0) == '.') && (FILE.path().extension() == "")) == false) {
                     if (isDerictoryExist(primalDirectoryPath / MyFolderName) == false)
                         fs::create_directory(primalDirectoryPath / MyFolderName); // Если сортировачная папка не созданна - создаем ее.
                     if (isDerictoryExist(primalDirectoryPath / MyFolderName / FILE.path().filename().string()) == false) {
                         fs::create_directory(primalDirectoryPath / MyFolderName / FILE.path().filename());
                         ui->textEdit->insertPlainText(QString::fromStdString(FILE.path().string() + " -> " + primalDirectoryPath.string() + "/" + MyFolderName + "/" + FILE.path().filename().string() + '\n'));
                         fs::copy(FILE, primalDirectoryPath / MyFolderName / FILE.path().filename().string(), fs::copy_options::recursive | fs::copy_options::skip_existing);
                         fs::remove_all(FILE);
                     }
                     else {
                         ui->textEdit->insertPlainText(QString::fromStdString(FILE.path().string()) + " is already existing at " + QString::fromStdString(primalDirectoryPath.string() + "/" + MyFolderName) + '\n');
                     }
                 }
             }
         }
        else { // сортировка не директорий
            if (isDerictoryExist(primalDirectoryPath / FILE.path().extension().string()) == false) // Если сортировачная папка не созданна - создаем ее.
                fs::create_directory(primalDirectoryPath / FILE.path().extension().string());
            ui->textEdit->insertPlainText(QString::fromStdString(FILE.path().string() + " -> " + primalDirectoryPath.string() + "/" + FILE.path().extension().string() + "\n"));
            fs::copy(FILE, primalDirectoryPath / FILE.path().extension().string(), fs::copy_options::skip_existing);
            fs::remove(FILE);
        }
    }
    ui->textEdit->insertPlainText("Done\n");
    delete primalFilesDerictoryIterator;
}


void SortingClass::on_pushButton_2_clicked()
{
   ui->lineEdit->setText(QFileDialog::getExistingDirectory(0, "Directory Dialog", ""));
}

