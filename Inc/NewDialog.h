#ifndef NEW_DIALOG_H
#define NEW_DIALOG_H

//ui include
#include "ui_NewDialog.h"

class NewDialog: public QWidget
{
  private:
    //member variables
    Ui_NewDialog* m_ui;

  public:
    //constructors
    NewDialog(QWidget* parent = 0);
    ~NewDialog();

    //public functions

    //getters

    //setters

  signals:
    void newProject(const QString& filePath, const QString& projectName);

  public slots:
    void browseButtonClicked();
    void createButtonClicked();
    void cancelButtonClicked();
    void nameTextChanged();
    void locationTextChanged();
    void projectTypeChanged();
}; //end class NewDialog: public QWidget

#endif //end ifndef NEW_DIALOG_H
