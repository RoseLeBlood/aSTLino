/*
 * The MIT License
 *
 * Copyright 2016 annas.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* 
 * File:   event.hpp
 * Author: annas
 *
 * Created on 11. November 2016, 14:39
 */

#ifndef _STD_EVENT_HPP_
#define _STD_EVENT_HPP_

#include "common.hpp"
#include "auto_ptr.hpp"
#include "list.hpp"
#include "eventargs.hpp"

namespace std 
{

    template<typename TYPE, class TSender = eventArgs>
    class delegate_base
    {
    public:
        using self_type = delegate_base<TYPE, TSender>;
        using const_self_type = const delegate_base<TYPE, TSender>;
        using sender_type = TSender;
        using value_type = TYPE;
        
	virtual bool operator == ( const_self_type* pOther) = 0;
	virtual void call( const sender_type* pSender, const value_type pParam) = 0;
    };

    template<class TReciever, typename TYPE, class TSender = object>
    class delegate : public delegate_base<TYPE, TSender>
    {
    private:
	typedef void (TReciever::*callFunction)(const TSender*, const TYPE pParam);
	callFunction         m_ptr2Func;
	TReciever*  m_ptr2Object;

    public:
	delegate(TReciever* p_ptr2Object, callFunction p_ptr2Func){
            m_ptr2Func      = p_ptr2Func;
            m_ptr2Object    = p_ptr2Object;
	}

	bool operator == (const delegate_base<TYPE, TSender>* pOther){
            const delegate<TReciever, TYPE, TSender>* other;
            other = static_cast<const delegate<TReciever, TYPE, TSender>*>(pOther);
            assert(other != NULL);
            assert(m_ptr2Object != NULL);
            return other->m_ptr2Object == m_ptr2Object && other->m_ptr2Func == m_ptr2Func;
	}
     

	virtual void call(const TSender* pSender,const TYPE pParam){
            assert(pSender != NULL);
            (m_ptr2Object->*m_ptr2Func)(pSender, pParam);
	}
    };
    template< typename TYPE, class TSender = object>
    class event
    {
    public:
	event() { }
	~event() { }

	void call( const TSender* pSender, const TYPE pParameter) {
            for(auto itr = m_observers.begin();
			itr != m_observers.end();
			itr++)
            {
                (*itr)->call(pSender, pParameter);
            }
        }

	void operator += ( const delegate_base<TYPE, TSender>* pHandler) {
            add(pHandler);
        }
	void operator -= ( const delegate_base<TYPE, TSender>* pHandler) {
            rem(pHandler);
        }
	void operator () ( const TSender* pSender, const TYPE pParameter) {
            call(pSender, pParameter);
        }
    private:
	void add( const delegate_base< TYPE, TSender>* pHandler) {
            assert(pHandler != NULL);
            m_observers.push_back(const_cast<delegate_base<TYPE, TSender>*>(pHandler));
        }
	void rem( const delegate_base<TYPE, TSender>* pHandler) {
            assert(pHandler != NULL);
            for(auto itr = m_observers.begin();
			itr != m_observers.end();
			itr++)
            {
                if(itr == pHandler)
                {
                    m_observers.erase(itr);
                    break;
                }
            }
        }
    private:
	std::list< delegate_base<TYPE, TSender>* > m_observers;
    };

	
}

#endif /* EVENT_HPP */

