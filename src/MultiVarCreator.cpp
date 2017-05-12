#include "MultiVarCreator.h"

//--------------------------------------------------
//constructors
//--------------------------------------------------
MultiVarCreator::MultiVarCreator(QWidget* parent)
  : QWidget(parent)
{
  m_ui = new Ui_MultiVarCreator();
  m_ui->setupUi(this);

  //connections
  connect(m_ui->cmbType, &QComboBox::currentIndexChanged,
          this, &MultiVarCreator::commonTypeChanged);
  connect(m_ui->txtSuffixes, &QTextEdit::textChanged,
          this, &MultiVarCreator::suffixesChanged);
  connect(m_ui->tabValues, &QTabWidget::tabBarClicked,
          this, &MultiVarCreator::valuesTabChanged);
  connect(m_ui->btnAdd, &QPushButton::clicked,
          this, &MultiVarCreator::addButtonClicked);
  connect(m_ui->btnClear, &QPushButton::clicked,
          this, &MultiVarCreator::clearButtonClicked);
} //end MultiVarCreator::MultiVarCreator(QWidget* parent)

MultiVarCreator::~MultiVarCreator()
{
  delete m_ui;
} //end MultiVarCreator::~MultiVarCreator()
