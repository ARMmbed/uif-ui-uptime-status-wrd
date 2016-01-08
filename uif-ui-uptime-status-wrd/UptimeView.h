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

#ifndef __UIF_UI_UPTIME_VIEW_H__
#define __UIF_UI_UPTIME_VIEW_H__

#include "UIFramework/UIView.h"
#include "UIFramework/UITextView.h"

#include "minar-platform/minar_platform_stats.h"

#undef printf

#if 0
#include "swo/swo.h"
#define printf(...) { swoprintf(__VA_ARGS__); }
#else
#define printf(...)
#endif




class UptimeView : public UIView
{
public:
    /*
        Create Text Monitor using a pointer to a variable.
    */
    UptimeView(const struct FontData* _font,
              uint32_t _interval = 1000)
        :   UIView(),
            font(_font),
            intervalInMilliseconds(_interval),
            variableString()
    {
        MBED_ASSERT(_variable);
        MBED_ASSERT(_font);

        getCurrentValue.attach(this, &UptimeView::getVariableValue);

        previousValue = getCurrentValue.call();

        updateImage(previousValue);
    }

    // from UIView
    virtual ~UptimeView(void)
    { }

    virtual uint32_t fillFrameBuffer(SharedPointer<FrameBuffer>& canvas, int16_t xOffset, int16_t yOffset)
    {
        /* read current value of variable */
        uint32_t currentValue = getCurrentValue.call();

        /* update image cell if value has changed */
        if (currentValue != previousValue)
        {
            updateImage(currentValue);

            /* store current value in cache */
            previousValue = currentValue;
        }

        /* copy image to canvas */
        if (variableCell)
        {
            variableCell->setInverse(inverse);
            variableCell->setHorizontalAlignment(align);
            variableCell->setVerticalAlignment(valign);
            variableCell->setWidth(width);
            variableCell->setHeight(height);

            variableCell->fillFrameBuffer(canvas, xOffset, yOffset);
        }

        return ULONG_MAX;
    }

    void setInterval(uint32_t interval)
    {
        intervalInMilliseconds = interval;
    }

private:
    /*
        Internal callback function when monitoring a pointer.
    */
    uint32_t getVariableValue(void)
    {
        uint32_t uptime = minar::stats::getUptime();

        printf("uptime: %lu\r\n", uptime);

        return uptime;
    }

    /*
        Helper function for creating a static Text image
        using the passed argument as value.
    */
    void updateImage(uint32_t value)
    {
        char string[12];

        // years
        if (value > 365 * 24 * 60 * 60)
        {
            snprintf(string, 10, "%lu years", value / (365 * 24 * 60 * 60));
        }
        // months
        else if (value > 30 * 24 * 60 * 60)
        {
            snprintf(string, 10, "%lu months", value / (30 * 24 * 60 * 60));
        }
        // days
        else if (value > 24 * 60 * 60)
        {
            snprintf(string, 10, "%lu days", value / (24 * 60 * 60));
        }
        // hours
        else if (value > 60 * 60)
        {
            snprintf(string, 10, "%lu hours", value / (60 * 60));
        }
        // minutes
        else if (value > 60)
        {
            snprintf(string, 10, "%lu min", value / 60);
        }
        // seconds
        else
        {
            snprintf(string, 10, "%lu sec", value);
        }

        variableString = string;

        variableCell = SharedPointer<UITextView>(new UITextView(variableString, font));
    }

private:
    const struct FontData* font;
    uint32_t* variable;
    uint32_t previousValue;
    uint32_t intervalInMilliseconds;
    uint32_t callCounter;

    FunctionPointer0<uint32_t> getCurrentValue;

    std::string variableString;
    SharedPointer<UITextView> variableCell;
};

#endif // __UIF_UI_UPTIME_VIEW_H__
