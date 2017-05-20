#ifndef NEW_DIALOG_H
#define NEW_DIALOG_H

//ui include
#include "ui_NewDialog.h"

#include "Manager.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo> //checking if file exists

#include <iostream>
#include <memory> //shared_ptr
#include <cctype> //isalnum

class NewDialog: public QWidget
{
    Q_OBJECT

  private:
    //member variables
    Ui_NewDialog* m_ui;
    std::shared_ptr<Manager> m_manager;

    //private functions
    bool isGoodPath(const QString& filePath);
    void normalizePath(QString& path);

  public:
    //constructors
    NewDialog(std::shared_ptr<Manager> manager, QWidget* parent = nullptr);
    ~NewDialog();

  signals:
    void newProject(const QString& filePath); //name is part of the path

  public slots:
    void browseButtonClicked();
    void createButtonClicked();
    void cancelButtonClicked();
    void nameTextChanged(const QString& newText);
    void locationTextChanged();
    void projectTypeChanged();
}; //end class NewDialog: public QWidget

#endif //end ifndef NEW_DIALOG_H
