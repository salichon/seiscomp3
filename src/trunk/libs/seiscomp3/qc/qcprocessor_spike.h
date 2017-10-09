/***************************************************************************
 *   Copyright (C) by GFZ Potsdam                                          *
 *                                                                         *
 *   You can redistribute and/or modify this program under the             *
 *   terms of the SeisComP Public License.                                 *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   SeisComP Public License for more details.                             *
 ***************************************************************************/


#ifndef __SEISCOMP_PROCESSING_QCPROCESSORSPIKE_H__
#define __SEISCOMP_PROCESSING_QCPROCESSORSPIKE_H__


#include <seiscomp3/qc/qcprocessor.h>


namespace Seiscomp {
namespace Processing {


DEFINE_SMARTPOINTER(QcProcessorSpike);

class SC_SYSTEM_CLIENT_API QcProcessorSpike : public QcProcessor {
	DECLARE_SC_CLASS(QcProcessorSpike);

	public:
		QcProcessorSpike();
		~QcProcessorSpike();

		typedef std::map<Core::Time, double> Spikes;
		Spikes getSpikes();

		bool feed(const Record *record);
		void _setFilter(double fsamp);

		bool setState(const Record* record, const DoubleArray& data);

	private:
		bool _initFilter;
};


}
}

#endif
