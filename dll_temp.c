
void splice_single(List* to, Node* pos_to, List* from, Node* pos_from) {
    assert(to != NULL);
    assert(from != NULL);

    // invalid or past end iterators
    if(pos_to == NULL || pos_from == NULL || pos_from->next == NULL) return;

    // -- deletion on from list
    Node* prev_from = pos_from->previous;
    Node* next_from = pos_from->next;

    next_from->previous = prev_from;

    // middle of from list
    if(prev_from != NULL) prev_from->next = next_from;
        // start of from list
    else from->first = next_from;

    --(from->length);
    // end of deletion

    // -- insertion on to list
    Node* prev_to = pos_to->previous;

    pos_from->previous = prev_to;
    pos_from->next = pos_to;

    if(prev_to != NULL) prev_to->next = pos_from;
        // start of to list
    else to->first = pos_from;

    pos_to->previous = pos_from;

    ++(to->length);
    // end of insertion
}

void splice(List* to, Node* pos, List* from, Node* first, Node* last) {
    if(first != last && first != NULL) {
        splice_single(to, pos, from, first);
        splice(to, pos, from, first->next, last);
    }
}

Node* insert(List* list, size_t idx, T val) {
    assert(list != NULL);

    // if out of bounds
    if(idx < 0 || idx > list->length) return NULL;
    // else a new node fits in list

    Node* prev = NULL;
    Node* next = list->first;

    int i;
    for(i = 0; i < idx; ++i) {
        prev = next;
        next = next->next;
    }

    Node* node = newNode(val, prev, next);
    if(prev != NULL) prev->next = node;
        // node is first on list
    else list->first = node;

    if(next != NULL) next->previous = node;
        // node is last on list
    else list->last = node;

    ++(list->length);

    return node;
}

Node* insert(List* list, Node* pos, T val) {
    assert(list != NULL);

    if(pos == NULL) return NULL;

    Node* prev = pos->previous;

    Node* node = newNode(val, prev, pos);

    if(prev != NULL) prev->next = node;
        // node is first on list
    else list->first = node;

    pos->previous = node;
    // never alter end of list

    ++(list->length);

    return node;
}

Node* erase(List* list, Node* pos) {
    assert(list != NULL);

    // invalid or past end iterator
    if(pos == NULL || pos->next == NULL) return NULL;

    Node* prev = pos->previous;
    Node* next = pos->next;

    next->previous = prev;
    // middle of list
    if(prev != NULL) prev->next = next;
        // start of list
    else list->first = next;

    freeNode(pos);
    --(list->length);

    return next;
}

Node* find(List* list, T val, Cmp cmp) {
    assert(list != NULL);

    Node* node = NULL;

    Node* current = list->first;
    for(int i = 0; i < list->length; ++i) {
        if(cmp(current->value, val) == 0) {
            node = current;
            break;
        }
        else current = current->next;
    }

    return node;
}

Node* find(List* list, T val, Cmp cmp ) {
    assert(list != NULL);

    Node* node = NULL;

    Node* current = list->first;
    for(int i = 0; i < list->length; ++i) {
        if(cmp(current->value, val) == 0) {
            node = current;
            break;
        }
        else current = current->next;
    }

    return node;
}

Node* delete(List* list, T val, Cmp cmp) {
    Node* target = find(list, val);

    if(target != NULL) {
        Node* prev = target->previous;
        Node* next = target->next;
        if(prev != NULL) {
            prev->next = next;
        }
            // removed is first in list
        else {
            list->first = next;
        }

        if(next != NULL) {
            next->previous = prev;
        }
            // removed is last in list
        else {
            list->last = prev;
        }

        target->previous = NULL;
        target->next = NULL;

        --(list->length);
    }

    return target;
}
