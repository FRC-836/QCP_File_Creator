#ifndef VAR_CREATOR_H
#define VAR_CREATOR_H

//#include "VarCreator_UI.h"
#include "ui_VarCreator.h"

#include "QcpGroup.h"
#include "CommandOptions.h"

#include <QVector>

#include <iostream>

class VarCreator: public QWidget
{
    Q_OBJECT

  private:
    //member variables
    Ui_VarCreator* m_ui;

  public:
    //constructors
    VarCreator(QWidget* parent = 0);
    ~VarCreator();

    //public functions

    //getters

    //setters

  signals:
    void groupCreated(const QcpGroup& newGroup);
    void groupChanged(const QcpGroup& updatedGroup);
    void valuesChanged();
    void constRequest(const QString& varName, QcpVariable& variable);

  public slots:
    void createGroupClicked();
    void changeGroupClicked();
    void headerCommentChanged(const QString& newText);
    void groupNameChanged(const QString& newText);
    void variableCreated(const QcpVariable& variable);
    void variablesCreated(const QVector<QcpVariable> variables);
    void changeGroup(const QcpGroup& newGroup);
    void valuesChangedHandle();
    void constRequestHandle(const QString& varName, QcpVariable& variable);
};

#endif //end ifndef VAR_CREATOR_H
