#include "MainWindow.h"

//--------------------------------------------------
//constructors
//--------------------------------------------------
MainWindow::MainWindow()
{
  m_ui = new Ui_MainWindow();
  m_ui->setupUi(this);

  //connections
  //connect(m_ui->btnNew, &QPushButton::clicked, this, &MainWindow::newButtonPressed);
  //connect(m_ui->btnOpen, &QPushButton::clicked, this, &MainWindow::openButtonPressed);
  //connect(m_ui->btnEditor, &QPushButton::clicked, this, &MainWindow::editorButtonPressed);
  //connect(m_ui->lstRecent, &QListWidget::currentItemChanged, this, &MainWindow::recentFileClicked);
} //end MainWindow::MainWindow()

MainWindow::~MainWindow()
{
  delete m_ui;
} //end MainWindow::~MainWindow()
