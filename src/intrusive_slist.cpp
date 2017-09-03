/*
 * The MIT License
 *
 * Copyright 2016 annas.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "include/intrusive_slist.hpp"

namespace std
{
    intrusive_slist_base::intrusive_slist_base()
    {
    }

    intrusive_slist_base::size_type intrusive_slist_base::size() const
    {
        size_type numNodes(0);
        const intrusive_slist_node* iter = &m_root;
        do
        {
            iter = iter->next;
            ++numNodes;
        } while (iter != &m_root);
        return numNodes - 1;
    }

    void intrusive_slist_base::link_after(intrusive_slist_node* node, intrusive_slist_node* prevNode)
    {
        assert(!node->in_list());
        node->next = prevNode->next;
        prevNode->next = node;
    }
    void intrusive_slist_base::unlink_after(intrusive_slist_node* node)
    {
        assert(node->in_list());
        intrusive_slist_node* thisNode = node->next;
        node->next = thisNode->next;
        thisNode->next = thisNode;
    }
}
