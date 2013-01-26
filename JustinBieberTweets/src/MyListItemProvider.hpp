/*
 * MyListItemProvider.hpp
 *
 *  Created on: 2013-01-19
 *      Author: Tony
 */

#ifndef MYLISTITEMPROVIDER_HPP_
#define MYLISTITEMPROVIDER_HPP_

#include <bb/cascades/ListItemProvider>
#include <bb/cascades/VisualNode>
#include <bb/cascades/ListView>

using namespace bb::cascades;

class MyListItemProvider : public bb::cascades::ListItemProvider {
public:
	MyListItemProvider();
	VisualNode* createItem(ListView *list, const QString &type);
	void updateItem(ListView *list, VisualNode *listItem, const QString &type, const QVariantList &indexPath, const QVariant &data);
};

#endif /* MYLISTITEMPROVIDER_HPP_ */
