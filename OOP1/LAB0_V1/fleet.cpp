#include "fleet.h"

void Fleet::remove_plane(string n)
{
	Elem_F* curr = first, * prev = nullptr, * old = nullptr;
	while (curr) {
		if (n == curr->plane->get_name()) {
			old = curr;
			if (!prev) {
				first = curr->next;
			}
			else {
				prev->next = curr->next;
			}
			curr = curr->next;
			delete old;
		}
	}
}

Fleet::Elem_F* Fleet::get_plane_range(int mini, int maxi)
{
	Elem_F* curr = first;
	Elem_F* planes = nullptr, * last = nullptr;
	while (curr) {
		if (curr->plane->get_capacity() <= maxi && curr->plane->get_capacity() >= mini) {
			Elem_F* tmp = new Elem_F(curr->plane);
			last = (!planes ? planes : last->next) = tmp;
		}
		curr = curr->next;
	}
	return planes;
}


