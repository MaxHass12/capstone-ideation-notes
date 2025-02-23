# 1. GraphQL Server

- GraphQL's philosophy is very different from REST. In REST every resoucr has its own address ie `/users/1`. All actions done to this resource are done via HTTP requests send to this endpoint.

- REST has limitations. For eg: We want to show the list of blogs, that were added by users who have commented on blogs our user follow.

- If the backend does not have an endpoint for this, then frontend has to send a lot of requests, and process them on the backend. This needs a lot of logic in frontend end and a lot of useless data is send from backend to frontend.

- A GraphQL server is well suited for these kind of situations.

- The main philosophy of GraphQL is that the code on the client forms a _query_ describing the data wanted and sends it to API via HTTP POST request. Unlike REST, all send to the same endpoint and their type is POST.

## 1.1 Schema and Queries

### 1.1.1 Schema

- At the heart of all GraphQL applications is a **schema** which describes

  1. The structure of the **types** of data sent between the client and the server. (The most basic _type_ is `Object` type)
  2. The relationship between different _types_.

- The GraphQL schema is defined using a human-readable **Schema Definition Language** For eg: The schema for the phonebook application is as follows:

```
type Person {
  name: String!
  phone: String
  street: String!
  city: String!
  id: ID!
}

type Query {
  personCount: Int!
  allPersons: [Person!]!
  findPerson(name: String!): Person
}
```

The above schema defines two _types_

1. `Person` is an object _type_ with 5 fields. 4/5 fields are of type `String`. 3 out of those 4 are mandatory - marked with `!`. `id` field is of type `ID`. `ID` type is a `String`, GraphQL ensures that they are mandatory.

2. The second type is `Query`. It describes what kind of queries can be made to the API. ()`Query` is the root type for unnamed operations.)

The above _Schema_ desribes 3 different types of queries - `personCount`, `allPersons` and `findPerson`. The `!` means that the returned vallue will not be `null`.

`[Person!]!` means that the query returns a list of `Person` object with the list containing no `null` values.

So, the schema describes what kind of queries can client send to server, what kind of params the query can have and what kind of data the queries return.

So, the schema describes what kind of queries can client send to server, what kind of params the query can have and what kind of data the queries return. In short, schema determines the contract between the client and the server.

### 1.1.2 Queries

The simplese of query `personCount` looks as follows

```
query {
  personCount
}
```

The response will be

```
{
  "data": {
    "personCount": 3
  }
}
```

For a query for which the return type is an Object, the query must specify which _fields_ of the object the query returns. For eg:

```
query {
  allPersons {
    name
    phone
  }
}
```

The response could be

```
{
  "data": {
    "allPersons": [
      {
        "name": "Arto Hellas",
        "phone": "040-123543"
      },
      {
        "name": "Matti Luukkainen",
        "phone": "040-432342"
      },
      {
        "name": "Venla Ruuska",
        "phone": null
      }
    ]
  }
}
```

For queries which take a param, that param needs to be specified inside round parens while the queried fields go inside the curly parens.

```
query {
  findPerson(name: "Arto Hellas") {
    phone
    city
    street
    id
  }
}
```

So, in contrast to REST, in GraphQL the query describes what kind of data it wants. In REST, the API endpoint just gives all the data that the backend is designed to give from that endpoint.

Note: Despite its name GraphQL has nothing to do with how the backend saves the data - relational or a document database or other servers which a GraphQL server can access.

## 1.2 Apollo Server

- `Apollo Server` is the leading JS GraphQL server library. It provides instances of `ApolloServer` which are used to **serve schema** and **handle requests**.

```
const server = new ApolloServer({
  typeDefs,
  resolvers,
})
```

- The Schema definition for `ApolloServer` is called `typeDef` and is a `string` describing the Schema.

- The second param is called an object called `resolvers` which describe how the _queries_ described in the Schema are resolved by the backend.

```
const resolvers = {
  Query: {
    personCount: () => persons.length,
    allPersons: () => persons,
    findPerson: (root, args) =>
      persons.find(p => p.name === args.name)
  }
}
```

- The `resolvers` defines `Query` as a field. (This is NOT GraphQL schema's `type Query`. ). The `resolvers.Query` is the implementation for `Query` defined in the schema. ( Also, in the above example `persons` has to be present somewhere in the code, Apollo Server can not magically create it for you)

- We say that every query has a resolver.

## 1.3 Apollo Studio Explorer

- When we run the dev server, we get a nice GUI "Apollo Studio Explorer" running at `4000`. Quite handy for sending queries.

## 1.4 Params of a Resolver

Now lets look at the resolver for `findPerson` ie `(root, args) => persons.find(p => p.name === args.name)`. 

The first param `arg` is a placeholder which we can ignore. The second param `args` is an object which contains all the params of the query.

PS: All resolver functions are given 4 params - `root`, `args`, `context`, and `info`.

## 1.5 The default Resolver


