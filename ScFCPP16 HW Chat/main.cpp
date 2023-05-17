// elements from STL like vectors have already been used here previously
// so i decided to add something else from the studied material
// 1. deque instead of vector to make access easier to both ends of the list msgs_
// 2. hush function for passwords
// 3. indexes to speed up searching in lists
// to implement item 1 added library <deque> and list msgs_ declared as deque. no more changes needed
// to implement item 2 added library <functional> that includes, among other things, hash functions 
// password hash is stored instead of password itself by registration 
// and by authorization password hash is compared with the previously entered one 


#include "chatroom.h"
//#include <iostream>

int main(void)
{
    chat::ChatRoom chatroom;
    chatroom.showMenu();

//#ifdef DEBUG
//#endif


    return 0;
}
