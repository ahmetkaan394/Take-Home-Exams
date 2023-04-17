#include "Browser.h"

Browser::Browser() {
    windows.append(Window());
}

void Browser::newWindow() {
    // TODO
    windows.prepend(Window());
}

void Browser::closeWindow() {
    // TODO
    if (windows.isEmpty()){
        return;
    }
    windows.removeNodeAtIndex(0);
}

void Browser::switchToWindow(int index) {
    // TODO
    windows.moveToIndex(index, 0);
}

Window &Browser::getWindow(int index) {
    return windows.getNodeAtIndex(index) -> data;
}

void Browser::moveTab(Window &from, Window &to) {
    // TODO
    if (from.isEmpty()){
        to.newTab(Tab());
        return;
    }
    else {
        to.newTab(from.getActiveTab());
        from.closeTab();
    }
}

void Browser::mergeWindows(Window &window1, Window &window2) {
    // TODO
    if (window2.isEmpty()){
        return;
    }
    else if (window1.isEmpty() && !(window2.isEmpty())){
        window2.changeActiveTabTo(0);
        while (!(window2.isEmpty())){
            window1.newTab(window2.getActiveTab());
            window2.closeTab();
        }
    }
    else {
        window2.changeActiveTabTo(0);
        while (!(window2.isEmpty())){
            moveTab(window2, window1);
        }
    }
}

void Browser::mergeAllWindows() {
    // TODO
    if (windows.isEmpty()){
        return;
    }
    else {
        if (windows.getSize() > 1){
            for (int i = 1; i < windows.getSize(); i++){
                mergeWindows(windows.getNodeAtIndex(0) -> data, windows.getNodeAtIndex(i) -> data);
            }
        }
    }
}

void Browser::closeAllWindows() {
    // TODO
    if (windows.isEmpty()){
        return;
    }
    windows.removeAllNodes();
}


void Browser::closeEmptyWindows() {
    // TODO
    if (windows.isEmpty()){
        return;
    }
    int size_of= windows.getSize();
    Node<Window>* temp = windows.getFirstNode();
    Node<Window>* temp2;
    for (int i = 0; i < size_of; i++){
        if ((temp->data).isEmpty()){
            temp2 = temp->next;
            windows.removeNode(temp);
            if(i != size_of -1){
                temp = temp2;
            }
        }
        else{
            temp = temp->next;
        }
    }
}

void Browser::print() {
    Node<Window> *head = windows.getFirstNode();
    if(head == NULL) {
        std::cout << "The browser is empty" << std::endl;
    } else {
        (head -> data).print();
        head = head -> next;
        while(head != windows.getFirstNode()) {
            (head -> data).print();
            head = head -> next;
        }
    }
}