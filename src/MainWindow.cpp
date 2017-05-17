#include "MainWindow.h"

//--------------------------------------------------
//private functions
//--------------------------------------------------
QString MainWindow::getOpenPath()
{
}

//--------------------------------------------------
//constructors
//--------------------------------------------------
MainWindow::MainWindow()
{
  //create the manager that all other widgets will use
  m_manager = std::make_shared<Manager>();

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
  std::cout << "deleting main window" << std::endl;
} //end MainWindow::~MainWindow()

//--------------------------------------------------
//public slots
//--------------------------------------------------
void MainWindow::newButtonPressed()
{
  NewDialog* newDialog= new NewDialog(this);
  newDialog->setWindowFlags(Qt::Window);
  newDialog->show();
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
