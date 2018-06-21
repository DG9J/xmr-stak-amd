 /*
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  * Additional permission under GNU GPL version 3 section 7
  *
  * If you modify this Program, or any covered work, by linking or combining
  * it with OpenSSL (or a modified version of that library), containing parts
  * covered by the terms of OpenSSL License and SSLeay License, the licensors
  * of this Program grant you additional permission to convey the resulting work.
  *
  */

#include "executor.h"
#include "minethd.h"
#include "jconf.h"
#include "console.h"
#include "donate-level.h"
#include "version.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>

//Do a press any key for the windows folk. *insert any key joke here*
#ifdef _WIN32
void win_exit()
{
	printer::inst()->print_str("Press any key to exit.");
	get_key();
	return;
}

#define strcasecmp _stricmp

#else
void win_exit() { return; }
#endif // _WIN32

void do_benchmark();

int main(int argc, char *argv[])
{
	const char* sFilename = "config.txt";
	if(!jconf::inst()->parse_config(sFilename))
	{
		win_exit();
		return 0;
	}

	if(!minethd::init_gpus())
	{
		win_exit();
		return 0;
	}

	do_benchmark();
	win_exit();
	return 0;
}

void do_benchmark()
{
	using namespace std::chrono;
	std::vector<minethd*>* pvThreads;

	enum { num_tests = 20 };

	printer::inst()->print_msg(L0, "Running a %ix10 second benchmark...", num_tests);

	uint8_t work[76] = {0};
	minethd::miner_work oWork = minethd::miner_work("", work, sizeof(work), 0, 1 << 22, 0);
	pvThreads = minethd::thread_starter(oWork);

	uint64_t iTotalCount = 0;
	uint64_t iTotalTime = 0;

	double fTotalHps[num_tests];

	for (int k = 0; k < num_tests; ++k)
	{
		const uint64_t iCurStamp = time_point_cast<milliseconds>(high_resolution_clock::now()).time_since_epoch().count();

		std::this_thread::sleep_for(std::chrono::seconds(10));

		fTotalHps[k] = 0.0;
		double fAveHps = 0.0;
		for (uint32_t i = 0; i < pvThreads->size(); i++)
		{
			const uint64_t count = (*pvThreads)[i]->iHashCount.exchange(0);
			const uint64_t dt = (*pvThreads)[i]->iTimestamp.exchange(0);

			iTotalCount += count;
			iTotalTime += dt;

			fTotalHps[k] += count * 1000.0 / dt;
			fAveHps += iTotalCount * 1000.0 / iTotalTime;
		}

		printer::inst()->print_msg(L0, "Average = %.1f H/S, Current = %.1f H/S", fAveHps, fTotalHps[k]);
	}

	std::sort(fTotalHps, fTotalHps + num_tests);

	double average12 = 0.0;
	for (int k = std::max(0, num_tests - 12); k < num_tests; ++k)
	{
		average12 += fTotalHps[k];
	}
	average12 /= 12.0;

	printer::inst()->print_msg(L0, "Average of 12 best results (much more consistent number) = %.1f H/S", average12);

	oWork = minethd::miner_work();
	minethd::switch_work(oWork);
}
