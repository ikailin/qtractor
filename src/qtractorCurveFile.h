// qtractorCurveFile.h
//
/****************************************************************************
   Copyright (C) 2005-2011, rncbc aka Rui Nuno Capela. All rights reserved.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*****************************************************************************/

#ifndef __qtractorCurveFile_h
#define __qtractorCurveFile_h

#include "qtractorCurve.h"


// Forward declarations.
class qtractorDocument;

class QDomElement;


//----------------------------------------------------------------------
// class qtractorCurveFile -- Automation curve file interface decl.
//

class qtractorCurveFile
{
public:

	// Constructor.
	qtractorCurveFile(qtractorCurveList *pCurveList)
		: m_pCurveList(pCurveList) {}

	// Destructor.	
	~qtractorCurveFile() { clear(); }

	// Curve list accessor.
	qtractorCurveList *list() const
		{ return m_pCurveList; }

	// Filename accessor.
	void setFilename(const QString& sFilename)
		{ m_sFilename = sFilename; }
	const QString& filename() const
		{ return m_sFilename; }

	// Curve item escriptor.
	struct Item
	{
		unsigned long    index;
		qtractorMidiEvent::EventType type;
		unsigned short   channel;
		unsigned short   param;
		qtractorCurve::Mode mode;
		bool             process;
		bool             capture;
		qtractorSubject *subject;
	};

	// Curve item list accessors.
	const QList<Item *>& items() const
		{ return m_items; }

	void addItem(Item *pCurveItem)
		{ m_items.append(pCurveItem); }
	
	// Curve item list cleanup.
	void clear()
	{
		qDeleteAll(m_items);
		m_items.clear();
	}

	// Curve item list serialization methods.
	bool save(qtractorDocument *pDocument,
		QDomElement *pElement, qtractorTimeScale *pTimeScale) const;
	bool load(qtractorDocument *pDocument,
		QDomElement *pElement, qtractorTimeScale *pTimeScale);
	bool apply(qtractorTimeScale *pTimeScale);

	// Text/curve-mode converters...
	static qtractorCurve::Mode modeFromText(const QString& sText);
	static QString textFromMode(qtractorCurve::Mode mode);

private:

	// Instance variables.
	qtractorCurveList *m_pCurveList;
	QString            m_sFilename;
	QList<Item *>      m_items;
};


#endif  // __qtractorCurveFile_h

