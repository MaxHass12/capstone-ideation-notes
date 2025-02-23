# 1. GraphQL Server

- GraphQL's philosophy is very different from REST. In REST every resoucr has its own address ie `/users/1`. All actions done to this resource are done via HTTP requests send to this endpoint.

- REST has limitations. For eg: We want to show the list of blogs, that were added by users who have commented on blogs our user follow.

- If the backend does not have an endpoint for this, then frontend has to send a lot of requests, and process them on the backend. This needs a lot of logic in frontend end and a lot of useless data is send from backend to frontend.

- A GraphQL server is well suited for these kind of situations.

- The main philosophy of GraphQL is that the code on the client forms a _query_ describing the data wanted and sends it to API via HTTP POST request. Unlike REST, all send to the same endpoint and their type is POST.

# 1.1 Schema and Queries

-
