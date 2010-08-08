/**
 ******************************************************************************
 *
 * @file       importexportgadgetfactory.h
 * @author     Edouard Lafargue Copyright (C) 2010.
 * @brief
 * @see        The GNU Public License (GPL) Version 3
 * @defgroup   importexportplugin
 * @{
 *
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef IMPORTEXPORTGADGETFACTORY_H_
#define IMPORTEXPORTGADGETFACTORY_H_

#include <coreplugin/iuavgadgetfactory.h>
#include "importexport_global.h"

namespace Core {
class IUAVGadget;
class IUAVGadgetFactory;
}

using namespace Core;

class IMPORTEXPORT_EXPORT ImportExportGadgetFactory : public IUAVGadgetFactory
{
    Q_OBJECT
public:
    ImportExportGadgetFactory(QObject *parent = 0);
    ~ImportExportGadgetFactory();

    Core::IUAVGadget *createGadget(QWidget *parent);
    IUAVGadgetConfiguration *createConfiguration(const QByteArray &state);
    IOptionsPage *createOptionsPage(IUAVGadgetConfiguration *config);
};

#endif // IMPORTEXPORTGADGETFACTORY_H_