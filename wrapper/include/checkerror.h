//
// Created by fengxuegt on 2025/7/11.
//

#ifndef CHECKERROR_H
#define CHECKERROR_H

#ifdef DEBUG
#define GL_LW_CALL(func) func;checkError()
#else
#define GL_LW_CALL(func) func
#endif
void checkError();



#endif //CHECKERROR_H
