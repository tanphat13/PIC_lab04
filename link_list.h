/* 
 * File:   link_list.h
 * Author: phat
 *
 * Created on November 4, 2019, 10:42 AM
 */

#ifndef LINK_LIST_H
#define	LINK_LIST_H

#ifdef	__cplusplus
extern "C"
{
#endif

#include "mcc.h"
   class Node {
   public:
      register_data pTask;
      Node *link;
      
      Node(register_data pTask) {
	 this->pTask = pTask;
	 this->link = NULL;
      }
   };

#ifdef	__cplusplus
}
#endif

#endif	/* LINK_LIST_H */

