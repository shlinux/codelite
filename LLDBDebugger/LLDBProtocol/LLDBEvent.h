#ifndef LLDBEVENT_H
#define LLDBEVENT_H

#include "cl_command_event.h"
#include "LLDBBacktrace.h"
#include "LLDBBreakpoint.h"
#include "LLDBLocalVariable.h"

class LLDBEvent : public clCommandEvent
{
    LLDBBacktrace m_backtrace;
    wxString      m_filename;
    int           m_linenumber;
    int           m_interruptReason;
    int           m_frameId;
    int           m_threadId;
    LLDBBreakpoint::Vec_t m_breakpoints;
    LLDBLocalVariable::Vect_t m_locals;
    int           m_variableId;

public:
    LLDBEvent(wxEventType eventType, int winid = 0);
    virtual ~LLDBEvent();
    LLDBEvent(const LLDBEvent& src);
    LLDBEvent& operator=(const LLDBEvent& src);
    virtual wxEvent* Clone() const {
        return new LLDBEvent(*this);
    }

    void SetLocals(const LLDBLocalVariable::Vect_t& locals) {
        this->m_locals.clear();
        this->m_locals.reserve( locals.size() );
        this->m_locals.insert(this->m_locals.end(), locals.begin(), locals.end());
    }

    void SetVariableId(int variableId) {
        this->m_variableId = variableId;
    }
    int GetVariableId() const {
        return m_variableId;
    }
    const LLDBLocalVariable::Vect_t& GetLocals() const {
        return m_locals;
    }
    void SetBacktrace(const LLDBBacktrace& backtrace) {
        this->m_backtrace = backtrace;
    }
    const LLDBBacktrace& GetBacktrace() const {
        return m_backtrace;
    }
    void SetLinenumber(int linenumber) {
        this->m_linenumber = linenumber;
    }
    int GetLinenumber() const {
        return m_linenumber;
    }

    void SetFrameId(int frameId) {
        this->m_frameId = frameId;
    }
    void SetThreadId(int threadId) {
        this->m_threadId = threadId;
    }
    int GetFrameId() const {
        return m_frameId;
    }
    int GetThreadId() const {
        return m_threadId;
    }
    /**
     * @brief return the Interrupt reason (wxEVT_LLDB_STOPPED)
     */
    int GetInterruptReason() const {
        return m_interruptReason;
    }

    void SetInterruptReason(int stopReason) {
        this->m_interruptReason = stopReason;
    }
    void SetBreakpoints(const LLDBBreakpoint::Vec_t& breakpoints) {
        this->m_breakpoints = breakpoints;
    }
    const LLDBBreakpoint::Vec_t& GetBreakpoints() const {
        return m_breakpoints;
    }
};

wxDECLARE_EVENT(wxEVT_LLDB_STOPPED,   LLDBEvent);
wxDECLARE_EVENT(wxEVT_LLDB_BACKTRACE, LLDBEvent);
wxDECLARE_EVENT(wxEVT_LLDB_EXITED,    LLDBEvent);
wxDECLARE_EVENT(wxEVT_LLDB_STARTED,   LLDBEvent);
wxDECLARE_EVENT(wxEVT_LLDB_STOPPED_ON_FIRST_ENTRY,   LLDBEvent);
wxDECLARE_EVENT(wxEVT_LLDB_RUNNING,   LLDBEvent);
wxDECLARE_EVENT(wxEVT_LLDB_BREAKPOINTS_UPDATED, LLDBEvent);
wxDECLARE_EVENT(wxEVT_LLDB_BREAKPOINTS_DELETED_ALL, LLDBEvent);
wxDECLARE_EVENT(wxEVT_LLDB_FRAME_SELECTED, LLDBEvent);
wxDECLARE_EVENT(wxEVT_LLDB_CRASHED, LLDBEvent);
wxDECLARE_EVENT(wxEVT_LLDB_LOCALS_UPDATED, LLDBEvent);
wxDECLARE_EVENT(wxEVT_LLDB_VARIABLE_EXPANDED, LLDBEvent);

typedef void (wxEvtHandler::*LLDBEventFunction)(LLDBEvent&);
#define LLDBEventHandler(func) \
    wxEVENT_HANDLER_CAST(LLDBEventFunction, func)

#endif // LLDBEVENT_H