#include "Window.h"

Window::Window() {
    this->activeTab = 0;
    tabs.append(Tab());
}

Tab Window::getActiveTab() {
    // TODO
    if (isEmpty()){
        return Tab();
    }
    else {
        return tabs.getNodeAtIndex(activeTab) -> data;
    }
}

bool Window::isEmpty() const {
    // TODO
    return tabs.isEmpty();
}

void Window::newTab(const Tab &tab) {
    // TODO
    if (isEmpty()){
        activeTab = 0;
        tabs.append(tab);
    }
    else {
        tabs.insertAfterNode(tab, tabs.getNodeAtIndex(activeTab));
        activeTab++;
    }
}

void Window::closeTab() {
    // TODO
    if (!isEmpty()){
        if (tabs.getSize() - 1 == activeTab){
            tabs.removeNodeAtIndex(activeTab);
            activeTab--;
        }
        
        else {
            tabs.removeNodeAtIndex(activeTab);
        }
        
    }
    else {
        activeTab = -1;
    }
}

void Window::moveActiveTabTo(int index) {
    // TODO
    tabs.moveToIndex(activeTab, index);
    activeTab = index;
}

void Window::changeActiveTabTo(int index) {
    // TODO
    if (index >= tabs.getSize() || index < 0){
        return;
    }
    activeTab = index;
}

void Window::addTab(Node<Tab> &tab) {
    // TODO
    if (isEmpty()){
        tabs.append(tab.data);
        activeTab= 0;
    }
    else {
        tabs.append(tab.data);
    }
}

void Window::print() {
    if(tabs.isEmpty()) std::cout << "Window is empty" << std::endl;
    else std::cout << "The active tab is tab " << activeTab << std::endl;
    tabs.print();
}
