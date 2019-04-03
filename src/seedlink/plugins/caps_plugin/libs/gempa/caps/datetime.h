/***************************************************************************
 * libcapsclient
 * Copyright (C) 2016  gempa GmbH
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/


#ifndef __GEMPA_CAPS_DATETIME_H__
#define __GEMPA_CAPS_DATETIME_H__

#ifdef WIN32
#include <winsock2.h>
#else
#include <sys/time.h>
#endif

#include <string>

struct tm;

namespace Gempa {
namespace CAPS {


class TimeSpan {
	// ----------------------------------------------------------------------
	//  Xstruction
	// ----------------------------------------------------------------------
	public:
		TimeSpan();
		TimeSpan(struct timeval*);
		TimeSpan(const struct timeval&);
		TimeSpan(double);
		TimeSpan(long secs, long usecs);

		//! Copy constructor
		TimeSpan(const TimeSpan&);


	// ----------------------------------------------------------------------
	//  Operators
	// ----------------------------------------------------------------------
	public:
		//! Comparison
		bool operator==(const TimeSpan&) const;
		bool operator!=(const TimeSpan&) const;
		bool operator< (const TimeSpan&) const;
		bool operator<=(const TimeSpan&) const;
		bool operator> (const TimeSpan&) const;
		bool operator>=(const TimeSpan&) const;

		//! Conversion
		operator double() const;
		operator const timeval&() const;

		//! Assignment
		TimeSpan& operator=(long t);
		TimeSpan& operator=(double t);

		//! Arithmetic
		TimeSpan operator+(const TimeSpan&) const;
		TimeSpan operator-(const TimeSpan&) const;

		TimeSpan& operator+=(const TimeSpan&);
		TimeSpan& operator-=(const TimeSpan&);


	// ----------------------------------------------------------------------
	//  Interface
	// ----------------------------------------------------------------------
	public:
		//! Returns the absolute value of time
		TimeSpan abs() const;

		//! Returns the seconds of the timespan
		long seconds() const;
		//! Returns the microseconds of the timespan
		long microseconds() const;

		//! Returns the (possibly negative) length of the timespan in seconds
		double length() const;

		//! Sets the seconds
		TimeSpan& set(long seconds);

		//! Sets the microseconds
		TimeSpan& setUSecs(long);

		//! Assigns the elapsed time to the passed out parameters
		void elapsedTime(int* days	, int* hours = NULL,
		                 int* minutes = NULL, int* seconds = NULL) const;

	// ----------------------------------------------------------------------
	//  Implementation
	// ----------------------------------------------------------------------
	protected:
		struct timeval _timeval;
};


class Time : public TimeSpan {
	// ----------------------------------------------------------------------
	// Public static data members
	// ----------------------------------------------------------------------
	public:
		static const Time Null;

	// ----------------------------------------------------------------------
	//  Xstruction
	// ----------------------------------------------------------------------
	public:
		Time();
		Time(long secs, long usecs);

		explicit Time(const TimeSpan&);
		explicit Time(const struct timeval&);
		explicit Time(struct timeval*);
		explicit Time(double);

		Time(int year, int month, int day,
		     int hour = 0, int min = 0, int sec = 0,
		     int usec = 0);

		//! Copy constructor
		Time(const Time&);


	// ----------------------------------------------------------------------
	//  Operators
	// ----------------------------------------------------------------------
	public:
		//! Conversion
		operator TimeSpan&();
		operator const TimeSpan&() const;
		operator bool() const;
		operator time_t() const;

		//! Assignment
		Time& operator=(const struct timeval& t);
		Time& operator=(struct timeval* t);
		Time& operator=(time_t t);
		Time& operator=(double t);

		//! Arithmetic
		Time operator+(const TimeSpan&) const;
		Time operator-(const TimeSpan&) const;
		TimeSpan operator-(const Time&) const;

		Time& operator+=(const TimeSpan&);
		Time& operator-=(const TimeSpan&);


	// ----------------------------------------------------------------------
	//  Interface
	// ----------------------------------------------------------------------
	public:
		//! Sets the time
		Time& set(int year, int month, int day,
		          int hour, int min, int sec,
		          int usec);

		//! Fill the parameters with the currently set time values
		//! @return The error flag
		bool get(int *year, int *month = NULL, int *day = NULL,
		         int *hour = NULL, int *min = NULL, int *sec = NULL,
		         int *usec = NULL) const;

		//! Fill the parameters with the currently set time values
		//! @return The error flag
		bool get2(int *year, int *yday = NULL,
		          int *hour = NULL, int *min = NULL, int *sec = NULL,
		          int *usec = NULL) const;

		//! Returns the current localtime
		static Time LocalTime();

		//! Returns the current gmtime
		static Time GMT();

     	/** Creates a time from the year and the day of the year
     	    @param year The year, including the century (for example, 1988)
     	    @param year_day The day of the year [0..365]
     	    @return The time value
     	 */
     	static Time FromYearDay(int year, int year_day);

		//! Saves the current localtime in the calling object
		Time& localtime();

		//! Saves the current gmtime in the calling object
		Time& gmt();

		//! Converts the time to localtime
		Time toLocalTime() const;

		//! Converts the time to gmtime
		Time toGMT() const;

		//! Returns whether the date is valid or not
		bool valid() const;

		/** Converts the time to string using format fmt.
		    @param fmt The format string can contain any specifiers
		               as allowed for strftime. Additional the '%f'
		               specifier is replaced by the fraction of the seconds.
                       Example:
		               toString("%FT%T.%fZ") = "1970-01-01T00:00:00.0000Z"
		    @return A formatted string
		 */
		std::string toString(const char* fmt) const;

		/**
		 * Converts the time to a string using the ISO time description
		 * @return A formatted string
		 */
		std::string iso() const;

		/** Converts a string into a time representation.
		    @param str The string representation of the time
		    @param fmt The format string containing the conversion
		               specification (-> toString)
		    @return The conversion result
		 */
		bool fromString(const char* str, const char* fmt);

		/** Static method to create a time value from a string.
			The parameters are the same as in Time::fromString.
     	 */
		static Time FromString(const char* str, const char* fmt);
};


}
}


#endif
