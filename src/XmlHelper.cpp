#include "XmlHelper.h"

//private functions
std::unique_ptr<XmlHelper::ProjectData_t> XmlHelper::parseProjectXmlOne()
{
  std::unique_ptr<ProjectData_t> data = std::make_unique<ProjectData_t>();
  QStack<Project::Tags::Tags> tags;
  bool processAttributes = false;
  bool processChars = false;

  while (!m_reader.atEnd())
  {
    switch (m_reader.readNext())
    {
      case QXmlStreamReader::EndDocument:
      {
        return data;
      } //end  case QXmlStreamReader::EndDocument:

      case QXmlStreamReader::StartElement:
      {
        //figure out which tag was read and if its valid
        auto foundAt = qFind(Project::TagsStr, m_reader.name());
        if (foundAt == Project::TagsStr.end())
        {
          //error encountered, raise it then break out of switch
          m_reader.raiseError("Tag " + m_reader.name() + " not recognized. Line: " +
                              QString::number(m_reader.lineNumber()));
          break;
        } //end  if (foundAt == Project::TagsStr.end())

        //no error, push tag ont stack and notifiy attributes need processed
        tags.push(static_cast<Project::Tags::Tags>(foundAt - Project::TagsStr.begin()));
        processAttributes = true;
        break;
      } //end  case QXmlStreamReader::StartElement:

      case QXmlStreamReader::EndElement:
      {
        //end tag reached, pop off the stack
        tags.pop();
        break;
      } //end  case QXmlStreamReader::EndElement:

      case QXmlStreamReader::Characters:
      {
        processChars = true;
        break;
      } //end  case QXmlStreamReader::Characters:

      default:
      {
        //do nothing, keep processing
        break;
      } //end  default:
    } //end  switch (m_reader.readNext())

    //process attributes of the most recently read tag
    if (processAttributes)
    {
      processAttributes = false;
      switch(tags.top())
      {
        case Project::Tags::CONSTANT:
        {
          //get attributes
          break;
        } //end  case Project::Tags::CONSTANT:
        case Project::Tags::ARRAY_CONSTANT:
        {
          //get attributes
          auto attribs = m_reader.attributes();

          //make sure all the required attributes exist
          if (!attribs.hasAttribute(Project::ArrayConstant::AttrStr[Project::ArrayConstant::Attributes::NAME]))
          {
            m_reader.raiseError("Required attribute \"" +
                                Project::ArrayConstant::AttrStr[Project::ArrayConstant::Attributes::NAME] +
                                " not found at line: " +
                                QString::number(m_reader.lineNumber()));
            break;
          } //end  if (!attribs.hasAttribute(Project::ArrayConstant::AttrStr[Project::ArrayConstant::Attributes::NAME]))
          if (!attribs.hasAttribute(Project::ArrayConstant::AttrStr[Project::ArrayConstant::Attributes::TYPE]))
          {
            m_reader.raiseError("Required attribute \"" +
                                Project::ArrayConstant::AttrStr[Project::ArrayConstant::Attributes::TYPE] +
                                " not found at line: " +
                                QString::number(m_reader.lineNumber()));
            break;
          } //end  if (!attribs.hasAttribute(Project::ArrayConstant::AttrStr[Project::ArrayConstant::Attributes::TYPE]))

          std::get<static_cast<int>(ProjectTuple::CONSTANT_LIST)>(*data);
          break;
        } //end  case Project::Tags::ARRAY_CONSTANT:
        case Project::Tags::QCP_FILE:
        {
          QString fileLocation = m_reader.attributes().value(Project::QcpFile::AttrStr[Project::QcpFile::Attributes::Location]).toString();
          //figure out which version of QcpFile XML it is then call appropriate parser
          break;
        } //end  case Project::Tags::QCP_FILE:
        default:
        {
          //the remaining tags have no attributes to process
          break;
        } //end  default:
      } //end  switch(tags.top())
    } //end  if (processAttributes)

    //handle characters that need to be processed
    if (processChars)
    {
      processChars = false;
      switch(tags.top())
      {
        case
      }
    }
  } //end  while (!m_reader.atEnd())

  return nullptr;
}
std::unique_ptr<XmlHelper::FileData_t> XmlHelper::parseFileXmlOne()
{
  return nullptr;
}
std::unique_ptr<XmlHelper::GroupData_t> XmlHelper::parseGroupXmlOne()
{
  return nullptr;
}

//constructors
XmlHelper::XmlHelper()
{
}

//public functions
std::unique_ptr<XmlHelper::ProjectData_t> XmlHelper::parseXml(const QString& location)
{
  //setup xml reader
  QFile xmlFile(location);
  m_reader.setDevice(&xmlFile);

  //create object to hold data
  std::unique_ptr<ProjectData_t> returnVal = nullptr;

  if (m_reader.readNextStartElement())
  {
    if (m_reader.name() == Project::TagsStr[Project::Tags::QCP_PROJECT])
    {
      //get attributes
      auto attributes = m_reader.attributes();

      //check that the version attribute exists, if not error out
      if (!attributes.hasAttribute(Project::QcpProject::AttrStr[Project::QcpProject::Attributes::VERSION]))
      {
        m_reader.raiseError("The Qcp Project File doesn't have a version number, can't be read");
      } //end  if (!attributes.hasAttribute(Project::QcpProject::AttrStr[Project::QcpProject::Attributes::VERSION]))
      else
      {
        QString version = attributes.value(Project::QcpProject::AttrStr[Project::QcpProject::Attributes::VERSION]).toString();

        //call proper version parser
        if (version == "1.0")
        {
          returnVal = parseProjectXmlOne();
        } //end  if (version == "1.0")
      } //end  else
    } //end  if (m_reader.name() == Project::TagsStr[Project::Tags::QCP_PROJECT])
    else
    {
      //not a QcpProject File
      m_reader.raiseError("The file is not a Qcp Project File. Can't be read.");
    } //end  else
  } //end  if (m_reader.readNextStartElement())

  //clear the xml reader and return the data
  m_reader.clear();
  return returnVal;
}
