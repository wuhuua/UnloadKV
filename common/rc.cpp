/*
Copyright (c) 2023 UnloadHome and/or its affiliates. All rights reserved.
UnloadKV is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details.
 */

/*
*   Created by wuhuua on 2023/9/27
*/

#include "rc.h"

const char *strrc(RC rc)
{
#define DEFINE_RC(name) \
  case RC::name: {      \
    return #name;       \
  } break;

  switch (rc) {
    DEFINE_RCS;
    default: {
      return "unkown";
    }
  }
#undef DEFINE_RC
}

bool OB_SUCC(RC rc) { return rc == RC::SUCCESS; }

bool OB_FAIL(RC rc) { return rc != RC::SUCCESS; }
