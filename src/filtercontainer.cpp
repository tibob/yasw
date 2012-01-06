#include "filtercontainer.h"
#include <QDebug>
#include "rotation.h"

/** \class FilterContainer
    \brief A QTabWidget to display the different filters.

    FilterContainer initialises each Filter.

    As QTabWidget::currentWidget only returns a QWidget and we need a FilterWidget and its virtual functions,
    we keep a Map between tabs indexes and FilterWidgets in tabToWidget.
    */


FilterContainer::FilterContainer( QWidget * parent)
    : QTabWidget(parent)
{
    oldIndex = -1;

    // initialise the filters
    baseFilter = new BaseFilter();
    tabToFilter.append(baseFilter); // as tabToFilter is empty, we start at index 0
    addTab(baseFilter->getWidget(), baseFilter->getName());

    //Rotation Filter
    Rotation *rotationFilter = new Rotation();
    tabToFilter.append(rotationFilter);
    addTab(rotationFilter->getWidget(), rotationFilter->getName());


    dekeystoningFilter = new Dekeystoning();
    tabToFilter.append(dekeystoningFilter);
    addTab(dekeystoningFilter->getWidget(), dekeystoningFilter->getName());

    connect(this, SIGNAL(currentChanged(int)),
            this, SLOT(tabChanged(int)));
}

FilterContainer::~FilterContainer()
{
    delete baseFilter;
}

void FilterContainer::setImage(QPixmap pixmap)
{
    tabToFilter[0]->setImage(pixmap);
    updateCurrentTabPixmap();
}

void FilterContainer::tabChanged(int index)
{
    updateCurrentTabPixmap(oldIndex); // we do not need to update Tabs before oldIndex
    oldIndex = index;
}

/*! \brief Ensure the current Filter works with the latest Pixmap.

    Lets the previous tabs (filters) recalculate their Pixmap so that current Tab
    gets the latest filtered Pixmap.

    \todo This could be a performance issue, caching may be a solution.

*/
void FilterContainer::updateCurrentTabPixmap(int fromIndex)
{
    int i;
    int currentTab = std::min (tabToFilter.size(), currentIndex());

    if (currentTab <= 0)    //either no tab (-1) or first tab (0)
        return;

    if (fromIndex < 1)      //no update of tab 0
        fromIndex = 1;

    if (fromIndex > currentTab) //no update of tab further current Tab
        fromIndex = currentTab;

    for (i = fromIndex; i <= currentTab; i++) {
        tabToFilter[i]->setImage(tabToFilter[i-1]->getFilteredImage());
    }
}
