/*
 * Copyright (C) 2012 Robert Chéramy (robert@cheramy.net)
 *
 * This file is part of YASW (Yet Another Scan Wizard).
 *
 * YASW is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * YASW is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with YASW.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "filtercontainer.h"
#include <QDebug>
#include "rotation.h"
#include "dekeystoning.h"
#include "cropping.h"

/** \class FilterContainer
    \brief A customised QTabWidget to display the different filters.

    FilterContainer initialises each Filter.

    As QTabWidget::currentWidget only returns a QWidget and we need a FilterWidget and its virtual functions,
    we keep a Map between tabs indexes and FilterWidgets in tabToWidget.
    */


FilterContainer::FilterContainer( QWidget * parent)
    : QTabWidget(parent)
{
    oldIndex = -1;

    // initialise the filters
// We do not need to display the "Base Filter" as it does not work (yet)
//    BaseFilter *baseFilter = new BaseFilter();
//    tabToFilter.append(baseFilter); // as tabToFilter is empty, we start at index 0
//    addTab(baseFilter->getWidget(), baseFilter->getName());

    //Rotation Filter
    Rotation *rotationFilter = new Rotation();
    tabToFilter.append(rotationFilter);
    addTab(rotationFilter->getWidget(), rotationFilter->getName());


    Dekeystoning *dekeystoningFilter = new Dekeystoning();
    tabToFilter.append(dekeystoningFilter);
    addTab(dekeystoningFilter->getWidget(), dekeystoningFilter->getName());

    Cropping *croppingFilter = new Cropping();
    tabToFilter.append(croppingFilter);
    addTab(croppingFilter->getWidget(), croppingFilter->getName());

    connect(this, SIGNAL(currentChanged(int)),
            this, SLOT(tabChanged(int)));
}

FilterContainer::~FilterContainer()
{
// TODO: free tabToFilter content.
}

void FilterContainer::setImage(QPixmap pixmap)
{
    // We do downscale the Pixmap to have better performance
    // TODO: Do a better job here (we should only downscale, compare width and height...)
    tabToFilter[0]->setImage(pixmap.scaledToHeight(1000));
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

    // NOTE: This could be a performance issue, caching may be a solution.

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

/*! \brief Get settings from the filters.

  Each Filter.getSettings will return its settings in a QMap<QString, QVariant>, which will be packed in another
  QMap (its type is QMap<QString, QMap<QString, QVariant> > ). The String Key is the value of Filter.getName().
  */
QMap<QString, QVariant> FilterContainer::getSettings()
{
    /* QVariant here is a QMap<QString, QVariant> */
    QMap<QString, QVariant> allSettings;
    BaseFilter *filter;


    foreach (filter, tabToFilter) {
        //BUG: getName() is localised, this can not be used for a configuration file
        allSettings[filter->getIdentifier()] = filter->getSettings();
    }

    return allSettings;
}

/*! \brief Set settings to the filters.

    See also FilterContainer::getSettings
  */
void FilterContainer::setSettings(QMap<QString, QVariant> settings)
{
    QString filterName;
    BaseFilter *filter;
    bool filterSet;

    foreach (filter, tabToFilter) {
        filterSet = false;
        foreach (filterName, settings.keys()) {
            if (filterName == filter->getIdentifier()) {
                filter->setSettings(settings[filterName].toMap());
                filterSet = true;
            }
        }
        if (filterSet == false) {
            /* we did not found settings for this filter, reset settings */
            filter->setSettings(QMap<QString, QVariant>());
        }
    }
}

