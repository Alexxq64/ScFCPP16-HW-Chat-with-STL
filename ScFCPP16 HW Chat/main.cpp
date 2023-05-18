// elements from STL like vectors have already been used here previously
// so i decided to add something else from the studied material
// 1. deque instead of vector to make access easier to both ends of the list msgs_
// 2. hush function for passwords
// 3. unordered_map instead of vector for users
// to implement item 1 added library <deque> and list msgs_ declared as deque. no more changes needed
// to implement item 2 added library <functional> that includes, among other things, hash functions 
// password hash is stored instead of password itself by registration 
// and by authorization password hash is compared with the previously entered one 
// to implement item 3 vector <user_> users_ changed to unordered_map <string id, mUser> mUsers_ and 
// user_(id, password, name) changed to mUser_(password, name) and
// accordingly all the necessary functions have been changed

/*Using unordered_map with string key and mUser values can be more efficient
when looking up users by their id, as the map uses hash table to provide O(1) average case lookup time. 
However, it can be less efficient than vector when iterating through all the users in the chat room, 
as vectors provide O(1) random access and contiguous memory access.
So, if you need to frequently look up users by their id, unordered_map might be a better choice. 
If you need to frequently iterate over all users in the chat room, vector might be a better choice.
*/


#include "mChatroom.h"

int main(void)
{
    chat::mChatRoom chatroom;
    chatroom.showMenu();


    return 0;
}
