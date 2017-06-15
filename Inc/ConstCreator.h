#ifndef CONST_CREATOR_H
#define CONST_CREATOR_H

#include "ui_ConstCreatorDialog.h"

#include "QcpVariable.h"
#include "Creator.h"
#include "CommandOptions.h"

#include <QVector>

#include <iostream>
#include <utility> //std::pair

class ConstCreator : public QWidget
{
    Q_OBJECT

  private:
    //member variables
    Ui_ConstCreatorDialog* m_ui;

    //private functions
    std::pair<bool, double> isValidDouble();
    std::pair<bool, QVector<double>> isValidDoubleArr();

  public:
    //constructors
    ConstCreator(Creator* caller, QWidget* parent = nullptr);
    ConstCreator(ConstCreator&) = delete;
    ConstCreator(ConstCreator&&) = delete;
    ~ConstCreator();

    //public functions

    //getters

    //setters

    //op overloads
    ConstCreator& operator=(const ConstCreator&) = delete;
    ConstCreator& operator=(ConstCreator&) = delete;

  signals:
    void newConstant(const QcpVariable& value);

  public slots:
    void createClicked();
    void cancelClicked();
    void nameChanged(const QString& newText);
    void valueChanged(const QString& newText);
    void typeChanged();
}; //end class ConstCreator

#endif //end #ifndef CONST_CREATOR_H
