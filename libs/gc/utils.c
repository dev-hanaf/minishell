#include "header.h"

t_data	*ft_gc_lstnew(void *ptr)
{
	t_data		*node;

	if (!ptr)
		return (NULL);
	node = (t_data *)malloc(sizeof(t_data));
	if (!node)
		return (NULL);
	node->ptr = ptr;
	node->next = NULL;
	return (node);
}

static void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*tmp_ptr;

	tmp_ptr = (unsigned char *)s;
	while (n > 0)
	{
		*(tmp_ptr++) = (unsigned char)c;
		n--;
	}
	return (s);
}

static void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}


void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	if (size && ((nmemb) > (SIZE_MAX / size)))
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
