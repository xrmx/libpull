/** \file coroutines.h
 * \brief Coroutines used to build the agents.
 * \author Antonio Langiu
 * \defgroup ag_coro
 * \{
 */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#ifdef __cplusplus
}
#endif /* __cplusplus */
#ifndef AGENTS_COROUTINE_H_
#define AGENTS_COROUTINE_H_

/** 
 * \brief PULL_BEGIN is a macro used to start the Duff's Device.
 * \param ev First event used to start the coroutine.
 */
#define PULL_BEGIN(ev)  \
    static agent_event_t current_event = ev; \
    static agent_msg_t agent_msg; \
    switch(current_event) { \
        FOREACH_IGNORED_EVENT(IGNORE_EVENT) \
        case ev:

/** 
* \brief  PULL_CONTINUE is a macro used to return to the caller function
* but preserving the state. When it is called it stores the current state
* and when the function is called again it starts from that state.
* 
* \param ev The current event that will be stored and returned to the caller.
* \param ev_data The data related to the event that may be used by the caller
* to perform some actions.
*/
#define PULL_CONTINUE(ev, ev_data) \
    do { \
        current_event = ev; \
        agent_msg.event = ev; \
        agent_msg.event_data = ev_data; \
        return agent_msg; \
        case ev:; \
    } while(0)

/** 
* \brief  PULL_FINISH is a macro that must be called at the end of each Duff's
* device. It closes the switch case and definitely reuturns to the calling
* function.
* 
* \param ev The even to be returned.
*/
#define PULL_FINISH(ev) \
        case ev: \
            agent_msg.event = ev; \
            agent_msg.event_data = NULL; \
            return agent_msg; \
    } \
    return agent_msg;

#define IGNORE_EVENT(event) case event:

#endif /* AGENTS_COROUTINE_H_ */
