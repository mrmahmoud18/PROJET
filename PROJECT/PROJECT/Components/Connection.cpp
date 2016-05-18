#include "Connection.h"

#include "Pin.h"
#include "../GUI/Interface.h"

Connection::Connection(Pin* r_InputPin, Pin* r_OutputPin, const std::vector< std::pair<int,int> >& r_Vertices)
{
    m_InputPin = r_InputPin;
    m_OutputPin =r_OutputPin;
    m_Vertices = r_Vertices;
}

void Connection::Update(const std::vector< std::pair<int,int> >& r_Vertices)
{
    m_Vertices = r_Vertices;
}

void Connection::Operate()
{
    m_OutputPin->SetStatus(m_InputPin->GetStatus());
}

void Connection::Draw(Interface* pInterface)
{
    pInterface->DrawConnection(m_Vertices, GetStatus());
    m_InputPin->Draw(pInterface);
    m_OutputPin->Draw(pInterface);
}

bool Connection::IsValidToOperate()
{
	return (m_InputPin->GetStatus() != Pin::FLOATING);
}

void Connection::ClearStatus()
{
	m_InputPin->SetStatus(Pin::FLOATING);
	m_OutputPin->SetStatus(Pin::FLOATING);
}
