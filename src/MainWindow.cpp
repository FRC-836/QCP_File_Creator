#include "MainWindow.h"

//--------------------------------------------------
//private functions
//--------------------------------------------------
QString MainWindow::getOpenPath()
{
  return QFileDialog::getOpenFileName(this,
                                      "Select QCP Project",
                                      QDir::homePath(),
                                      "Project (*"+Project::PROJECT_FILE_EXTENSION+")");
}

//--------------------------------------------------
//constructors
//--------------------------------------------------
MainWindow::MainWindow()
{
  //TODO load recently opened files

  //setup the UI
  m_ui = new Ui_MainWindow();
  m_ui->setupUi(this);

  //connections
  connect(m_ui->btnNew, &QPushButton::clicked, this, &MainWindow::newButtonPressed);
  connect(m_ui->btnOpen, &QPushButton::clicked, this, &MainWindow::openButtonPressed);
  connect(m_ui->btnEditor, &QPushButton::clicked, this, &MainWindow::editorButtonPressed);
  connect(m_ui->lstRecent, &QListWidget::itemClicked, this, &MainWindow::recentFileClicked);
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
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "INFO: MainWindow: Recieved new button pressed call" << std::endl;
  }

  //create a NewDialog for the user to create the new project with
  NewDialog* newDialog = new NewDialog(this);
  newDialog->setWindowFlags(Qt::Window); //make its own window
  newDialog->show();

  connect (newDialog, &NewDialog::newProject, this, &MainWindow::newProjectCreated);

  //this now longer needs to be shown unless newdialog is canceled
  this->hide();
} //end void MainWindow::newButtonPressed()
void MainWindow::openButtonPressed()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "INFO: MainWindow: Recieved open button pressed call" << std::endl;
  }

  QString filePath = getOpenPath();

  Creator* creator = new Creator();
  m_creators.push_back(creator);
  creator->openProject(filePath, false);
  creator->show();

  this->hide();
} //end void MainWindow::openButtonPressed()
void MainWindow::editorButtonPressed()
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "INFO: MainWindow: Recieved editor button pressed call" << std::endl;
  }

  QString filePath = getOpenPath();

  Creator* creator = new Creator();
  m_creators.push_back(creator);
  creator->openProject(filePath, true);
  creator->show();

  this->hide();
} //end void MainWindow::editorButtonPressed()
void MainWindow::recentFileClicked(QListWidgetItem* item)
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "INFO: MainWindow: Recieved recent file clicked call" << std::endl;
  }

  QString filePath = item->text();

  Creator* creator = new Creator();
  m_creators.push_back(creator);
  creator->openProject(filePath, false);
  creator->show();
} //end void MainWindow::recentFileClicked(QListWidgetItem* item)
void MainWindow::newProjectCreated(const QString& name, const QString& filePath)
{
  if (CmdOptions::verbosity >= CmdOptions::DEBUG_LEVEL::ALL_INFO)
  {
    std::cout << "INFO: MainWindow: Recieved new project creation call" << std::endl;
  }

  Creator* creator = new Creator();
  m_creators.push_back(creator);
  creator->createProject(name, filePath);
  creator->show();
}
