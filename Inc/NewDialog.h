#ifndef NEW_DIALOG_H
#define NEW_DIALOG_H

//ui include
#include "ui_NewDialog.h"

#include "Manager.h"

#include <iostream>
#include <memory>

class NewDialog: public QWidget
{
    Q_OBJECT

  private:
    //member variables
    Ui_NewDialog* m_ui;
    std::shared_ptr<Manager> m_manager;

    //private functions
    bool isGoodPath(const QString& filePath);

  public:
    //constructors
    NewDialog(std::shared_ptr<Manager> manager, QWidget* parent = nullptr);
    ~NewDialog();

    //public functions

    //getters

    //setters

  signals:
    void newProject(const QString& filePath); //name is part of the path

  public slots:
    void browseButtonClicked();
    void createButtonClicked();
    void cancelButtonClicked();
    void nameTextChanged(const QString& newText);
    void locationTextChanged(const QString& newText);
    void projectTypeChanged();
}; //end class NewDialog: public QWidget

#endif //end ifndef NEW_DIALOG_H
