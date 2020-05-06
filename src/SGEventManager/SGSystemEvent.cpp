#include "SGSystemEvent.h"
#include "SGLog.h"
using namespace SG;

const EventType SG::Evt_Word::sk_EventType(0x950108bb);
const EventType SG::Evt_CameraMove::sk_EventType(0x8bff3aa0);
const EventType SG::Evt_CameraScroll::sk_EventType(0x64bce85d);
const EventType SG::Evt_CameraPosMove::sk_EventType(0xb4c2314b);

IEventDataPtr SG::Evt_Word::Copy(void) const
{
	return IEventDataPtr(SG_NEW Evt_Word(m_output));
}

IEventDataPtr SG::Evt_CameraMove::Copy(void) const
{
	return IEventDataPtr(SG_NEW Evt_CameraMove(x_offset, y_offset));
}

IEventDataPtr SG::Evt_CameraScroll::Copy(void) const
{
	return IEventDataPtr(SG_NEW Evt_CameraScroll(scroll));
}

IEventDataPtr SG::Evt_CameraPosMove::Copy(void) const
{
	return IEventDataPtr(SG_NEW Evt_CameraPosMove(move, deltaTime));
}
