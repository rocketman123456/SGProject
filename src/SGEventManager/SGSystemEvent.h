#pragma once
#include "SGIEventData.h"
#include "SGMemoryMacros.h"
#include "SGCamera.h"
#include <string>

namespace SG
{
	class Evt_Word : implements BaseEventData
	{
	public:
		std::string m_output;
		static const EventType sk_EventType;
		explicit Evt_Word(const std::string& out = "Hello") :m_output(out) {}
		virtual const EventType& GetEventType(void) const override { return sk_EventType; }
		virtual double GetTimeStamp(void) const override { return m_timeStamp; }
		virtual void Serialize(std::ostrstream& out) const override {}
		virtual void Deserialize(std::istrstream& in) override {}
		virtual IEventDataPtr Copy(void) const override;
		virtual const char* GetName(void) const override { return "Evt_Word"; }
	};

	class Evt_CameraMove : implements BaseEventData
	{
	public:
		double x_offset;
		double y_offset;
		static const EventType sk_EventType;
		explicit Evt_CameraMove(double x = 0, double y = 0) :x_offset(x), y_offset(y) {}
		virtual const EventType& GetEventType(void) const override { return sk_EventType; }
		virtual double GetTimeStamp(void) const override { return m_timeStamp; }
		virtual void Serialize(std::ostrstream& out) const override {}
		virtual void Deserialize(std::istrstream& in) override {}
		virtual IEventDataPtr Copy(void) const override;
		virtual const char* GetName(void) const override { return "Evt_CameraMove"; }
	};

	class Evt_CameraScroll : implements BaseEventData
	{
	public:
		double scroll;
		static const EventType sk_EventType;
		explicit Evt_CameraScroll(double s = 0) :scroll(s) {}
		virtual const EventType& GetEventType(void) const override { return sk_EventType; }
		virtual double GetTimeStamp(void) const override { return m_timeStamp; }
		virtual void Serialize(std::ostrstream& out) const override {}
		virtual void Deserialize(std::istrstream& in) override {}
		virtual IEventDataPtr Copy(void) const override;
		virtual const char* GetName(void) const override { return "Evt_CameraMove"; }
	};

	class Evt_CameraPosMove : implements BaseEventData
	{
	public:
		Camera_Movement move;
		double deltaTime;
		static const EventType sk_EventType;
		explicit Evt_CameraPosMove(Camera_Movement m = FORWARD, double dt = 0) :move(m), deltaTime(dt) {}
		virtual const EventType& GetEventType(void) const override { return sk_EventType; }
		virtual double GetTimeStamp(void) const override { return m_timeStamp; }
		virtual void Serialize(std::ostrstream& out) const override {}
		virtual void Deserialize(std::istrstream& in) override {}
		virtual IEventDataPtr Copy(void) const override;
		virtual const char* GetName(void) const override { return "Evt_CameraMove"; }
	};
}
