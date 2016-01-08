/* mbed
 * Copyright (c) 2006-2015 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "uif-ui-uptime-status-wrd/UptimeStatusTable.h"

#include "UIFramework/UITextView.h"
#include "UIFramework/UITextMonitorView.h"

#include "uif-ui-uptime-status-wrd/DutyCycleView.h"
#include "uif-ui-uptime-status-wrd/UptimeView.h"

#if 0
#include "swo/swo.h"
#define printf(...) { swoprintf(__VA_ARGS__); }
#else
#undef printf
#define printf(...)
#endif

typedef enum {
    CELL_TOP_FILLER = 0,
    CELL_TIME_TITLE,
    CELL_MID_FILLER_1,
    CELL_TIME_VALUE,
    CELL_MID_FILLER_2,
    CELL_CHARGE_TITLE,
    CELL_MID_FILLER_3,
    CELL_CHARGE_VALUE,
    CELL_END_FILLER
} entries_t;

SharedPointer<UIView> UptimeStatusTable::viewAtIndex(uint32_t index) const
{
    UIView* cell = NULL;

    switch(index)
    {
        case CELL_TIME_TITLE:
                            cell = new UITextView("duty cycle", &Font_Breadcrumbs);
                            break;

        case CELL_TIME_VALUE:
                            cell = new DutyCycleView(&Font_Menu);
                            break;

        case CELL_CHARGE_TITLE:
                            cell = new UITextView("uptime", &Font_Breadcrumbs);
                            break;

        case CELL_CHARGE_VALUE:
                            cell = new UptimeView(&Font_Menu);
                            break;

        case CELL_TOP_FILLER:
        case CELL_MID_FILLER_1:
        case CELL_MID_FILLER_2:
        case CELL_MID_FILLER_3:
        case CELL_END_FILLER:
        default:
                            cell = new UIImageView(NULL);
                            break;
    }

    if (cell)
    {
        cell->setHorizontalAlignment(UIView::ALIGN_CENTER);
        cell->setVerticalAlignment(UIView::VALIGN_MIDDLE);
        cell->setWidth(0);
        cell->setHeight(0);
    }

    return SharedPointer<UIView>(cell);
}

uint32_t UptimeStatusTable::getSize() const
{
    return CELL_END_FILLER + 1;
}

uint32_t UptimeStatusTable::widthAtIndex(uint32_t index) const
{
    (void) index;

    return 128;
}

uint32_t UptimeStatusTable::heightAtIndex(uint32_t index) const
{
    uint32_t ret = 0;

    switch(index)
    {
        case CELL_TIME_TITLE:
        case CELL_CHARGE_TITLE:
                                ret = 7;
                                break;

        case CELL_TIME_VALUE:
                                ret = 31;
                                break;

        case CELL_CHARGE_VALUE:
                                ret = 31;
                                break;

        case CELL_TOP_FILLER:
                                ret = 24; // 11 + 13
                                break;

        case CELL_MID_FILLER_1:
        case CELL_MID_FILLER_2:
        case CELL_MID_FILLER_3:
                                ret = 6;
                                break;

        case CELL_END_FILLER:
                                ret = 10; // 11 + 5
                                break;
        default:
                                ret = 0;
                                break;
    }

    return ret;
}

SharedPointer<UIView::Action> UptimeStatusTable::actionAtIndex(uint32_t index)
{
    (void) index;

    SharedPointer<UIView::Action> returnObject(new UIView::Action);

    return returnObject;
}

const char* UptimeStatusTable::getTitle() const
{
    return "";
}

uint32_t UptimeStatusTable::getFirstIndex() const
{
    return CELL_TOP_FILLER;
}

uint32_t UptimeStatusTable::getLastIndex() const
{
    return CELL_END_FILLER;
}

uint32_t UptimeStatusTable::getDefaultIndex() const
{
    return CELL_TOP_FILLER;
}
