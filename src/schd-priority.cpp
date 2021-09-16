/**
 * Copyright 2020 Hung-Hsin Chen, LSA Lab, National Tsing Hua University
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "scheduler.h"


bool schd_priority(const valid_candidate_t &a, const valid_candidate_t &b) {
  if (a.missing > 0 && b.missing > 0) //missing = requirement - usage
    return a.missing / (a.missing + a.usage) > b.missing / (b.missing + b.usage); //如果a和b均未达到requirement,则选择使用率距离其要求值最远的那个容器
  if (a.missing > 0 && b.missing < 0) return true; //如果容器b已经达到requirement，则优先选择容器a，容器a往队列前端排
  if (a.missing < 0 && b.missing > 0) return false;//如果容器a已经达到requirement，则优先选择容器b，容器b往队列前端排
  // return a.arrived_time < b.arrived_time; // first-arrival first
  return a.usage < b.usage;  // minimum usage first 如果队列中所有容器都已经达到requirement，则选择当前使用率最低的那个容器，让其往队列前端排
}
