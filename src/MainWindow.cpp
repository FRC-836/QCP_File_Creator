#include "MainWindow.h"

//--------------------------------------------------
//private functions
//--------------------------------------------------
QString MainWindow::getOpenPath()
{
  return QFileDialog::getOpenFileName(this,
                                      "Select QCP Project",
                                      QDir::homePath(),
                                      "Project (*"+Manager::FILE_EXTENSION+")");
}

//--------------------------------------------------
//constructors
//--------------------------------------------------
MainWindow::MainWindow()
{
  //create the manager that all other widgets will use
  m_manager = std::make_shared<Manager>();

  //TODO load recently opened files

  //setup the UI
  m_ui = new Ui_MainWindow();
  m_ui->setupUi(this);

  //connections
  connect(m_ui->btnNew, &QPushButton::clicked, this, MainWindow::newButtonPressed);
  connect(m_ui->btnOpen, &QPushButton::clicked, this, MainWindow::openButtonPressed);
  connect(m_ui->btnEditor, &QPushButton::clicked, this, MainWindow::editorButtonPressed);
  connect(m_ui->lstRecent, &QListWidget::itemClicked, this, MainWindow::recentFileClicked);
  connect(this, &MainWindow::openProject, m_manager.get(), &Manager::openProject);
} //end MainWindow::MainWindow()

MainWindow::~MainWindow()
{
  delete m_ui;

  //debug ipurposes
  if (CmdOptions::verbosity == CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "deleting main window" << std::endl;
  }
} //end MainWindow::~MainWindow()

//--------------------------------------------------
//public slots
//--------------------------------------------------
void MainWindow::newButtonPressed()
{
  //create a NewDialog for the user to create the new project with
  NewDialog* newDialog= new NewDialog(m_manager, this);
  newDialog->setWindowFlags(Qt::Window); //make its own window
  newDialog->show();

  //this now longer needs to be shown unless newdialog is canceled
  this->hide();
} //end void MainWindow::newButtonPressed()
void MainWindow::openButtonPressed()
{
  QString filePath = getOpenPath();
  emit openProject(filePath, false);
} //end void MainWindow::openButtonPressed()
void MainWindow::editorButtonPressed()
{
  QString filePath = getOpenPath();
  emit openProject(filePath, true);
} //end void MainWindow::editorButtonPressed()
void MainWindow::recentFileClicked(QListWidgetItem* item)
{
  QString filePath = item->text();
  emit openProject(filePath, false);
} //end void MainWindow::recentFileClicked(QListWidgetItem* item)
