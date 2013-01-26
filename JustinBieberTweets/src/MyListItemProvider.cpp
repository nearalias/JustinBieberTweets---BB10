/*
 * MyListItemProvider.cpp
 *
 *  Created on: 2013-01-19
 *      Author: Tony
 */

#include "MyListItemProvider.hpp"
#include "MyItemClass.hpp"

MyListItemProvider::MyListItemProvider(){

}

VisualNode* MyListItemProvider::createItem(ListView *list, const QString &type){
	MyItemClass *myItem = new MyItemClass();
	return myItem;
}

void MyListItemProvider::updateItem(ListView *list, VisualNode *listItem, const QString &type, const QVariantList &indexPath, const QVariant &data){
	MyItemClass *myItem = static_cast<MyItemClass*>(listItem);
	myItem->updateItem(data.toStringList());
}




