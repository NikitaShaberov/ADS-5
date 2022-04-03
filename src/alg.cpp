#include <string>
#include <map>
#include "tstack.h"


int getpriorite(char sim) {
switch (sim) {
case '(':
return 0;
case ')':
return 1;
case '+':
return 2;
case '-':
return 2;
case '*':
return 3;
case '/':
return 3;
case ' ':
return -2;
default:
return -1;
}
}

void split(char sim, std::string* str) {
*str += sim;
*str += ' ';
}

int count(int a, int b, char c) {
switch (c) {
case '+':
return b + a;
case '-':
return b - a;
case '*':
return b * a;
case '/':
return b / a;
default:
throw "Error perform actions!";
}
}

std::string infx2pstfx(std::string inf) {
TStack<char, 128> stack1;
std::string res = "";
for (int i = 0; i < inf.length(); i++) {
if (getpriorite(inf[i]) == -1) {
if (i < inf.length() && getpriorite(inf[i + 1]) == -1) {
while (i < inf.length() && getpriorite(inf[i]) == -1) {
res += inf[i];
i++;
}
res += ' ';
} else {
split(inf[i], &res);
}
continue;
}
if (stack1.isEmpty() ||getpriorite(inf[i]) == 0
|| getpriorite(inf[i]) > getpriorite(stack1.get())) {
stack1.push(inf[i]);
} else {
if (getpriorite(inf[i]) == 1) {
while (getpriorite(stack1.get()) != 0) {
split(stack1.get(), &res);
stack1.pop();
}
stack1.pop();
} else if (getpriorite(inf[i]) <=getpriorite(stack1.get())) {
while (getpriorite(stack1.get()) > 1) {
split(stack1.get(), &res);
stack1.pop();
}
stack1.push(inf[i]);
}
}
}
while (!stack1.isEmpty()) {
if (getpriorite(stack1.get()) > 1) {
split(stack1.get(), &res);
}
stack1.pop();
}
res.pop_back();
return res;
}
int eval(std::string post) {
TStack<int, 100> stack2;
for (int i = 0; i < post.length(); i++) {
int r = i;
std::string temp = "";
while (getpriorite(post[r]) == -1) {
temp += post[r];
r++;
}
i = r;
if (getpriorite(post[i]) > 1) {
int a = stack2.get();
stack2.pop();
int b = stack2.get();
stack2.pop();
stack2.push(count(a, b, post[i]));
}
if (temp != "") {
stack2.push(std::stoi(temp));
}
}
return stack2.get();
}
