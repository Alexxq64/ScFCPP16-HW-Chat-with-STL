// elements from STL like vectors have already been used here previously
// so i decided to add something else from the studied material
// 1. deque instead of vector to make access easier to both ends of the list msgs_
// 2. hush function for passwords
// 3. unordered_map instead of vector for users
// to implement item 1 added library <deque> and list msgs_ declared as deque. no more changes needed
// to implement item 2 added library <functional> that includes, among other things, hash functions 
// password hash is stored instead of password itself by registration 
// and by authorization password hash is compared with the previously entered one 

/*Using a std::unordered_map with std::string keys and User values can be more efficient
when looking up users by their id, as the map uses a hash table to provide O(1) average case lookup time. 
However, it can be less efficient than a vector when iterating through all the users in the chat room, 
as vectors provide O(1) random access and contiguous memory access.
Using a std::vector with User elements can be more efficient when iterating through all users in the chat room, 
as vectors provide O(1) random access and contiguous memory access. 
However, it can be less efficient when looking up users by their id, as you would need to iterate 
over the entire vector to find the user with the matching id, resulting in O(n) worst case lookup time.
So, if you need to frequently look up users by their id, a std::unordered_map might be a better choice. 
If you need to frequently iterate over all users in the chat room, a std::vector might be a better choice.
*/


#include "mChatroom.h"
#ifndef DEBUG
#include "chatroom.h"
#endif
//#include <iostream>

int main(void)
{
#ifndef DEBUG
    chat::ChatRoom chatroom;
    chatroom.showMenu();

#endif
    chat::mChatRoom chatroom;
    chatroom.showMenu();


    return 0;
}
