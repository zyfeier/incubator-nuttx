/****************************************************************************
 * sched/sched/sched_gettasklist.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <semaphore.h>
#include <nuttx/mqueue.h>

#include "sched/sched.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: nxsched_get_tasklist
 *
 * Description:
 *   This function adds a TCB to one of the blocked state task lists as
 *   inferred from task_state.
 *
 * Input Parameters:
 *   btcb - Points to the TCB that is blocked
 *   task_state - identifies the state of the blocked task
 *
 * Returned Value:
 *   None
 *
 * Assumptions:
 * - The caller has established a critical section before
 *   calling this function.
 *
 ****************************************************************************/

dq_queue_t *nxsched_get_tasklist(FAR struct tcb_s *btcb,
                                 tstate_t task_state)
{
  if (task_state == TSTATE_WAIT_SEM && btcb->waitsem)
    {
      return SEM_WAIT_TLIST(btcb->waitsem);
    }
  else if (task_state == TSTATE_WAIT_MQNOTEMPTY && btcb->msgwaitq)
    {
      return MQ_WNE_TLIST(btcb->msgwaitq);
    }
  else if (task_state == TSTATE_WAIT_MQNOTFULL && btcb->msgwaitq)
    {
      return MQ_WNF_TLIST(btcb->msgwaitq);
    }
  else
    {
      return g_tasklisttable[task_state].list;
    }
}
