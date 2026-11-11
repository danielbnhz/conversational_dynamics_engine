# Conversational Dynamics Engine (CDE)

## Project Direction

The **Conversational Dynamics Engine (CDE)** is intended to be a real-time system for analyzing and predicting general conversational dynamics. Its purpose is not merely to classify individual sentences or generate replies. It should build and update a structured understanding of an evolving conversation, estimate what may happen next, and represent uncertainty when several interpretations remain plausible.

The long-term ambition is an engineering-grade analytical application: a system capable of examining conversational structure, relationships, context, and change over time with substantial computational depth where that depth is useful.

## Core Technology

- **C++20** is the primary application and systems language.
- **Qt 6 Widgets** provides the desktop application and interactive analytical interface.
- **Python and Transformer-based NLP models** provide language-processing capabilities.
- **SQLite** is the initial persistent storage layer.
- Communication between the C++ application and Python services can initially use a separate process and structured JSON messages, keeping the application architecture modular.

The intended division of responsibility is:

- **C++ / Qt:** application lifecycle, data structures, conversation state, ingestion orchestration, persistence, prediction coordination, experiment management, and visualization.
- **Python / Transformers:** language-model inference, embeddings, dialogue-act analysis, semantic features, and other NLP tasks that benefit from the Python ecosystem.
- **Shared data contracts:** explicit, versionable message and result formats between components.

This division is a starting architecture, not a permanent constraint. Components should be replaceable when evidence shows a better design.

## What the Engine Should Analyze

CDE should treat conversation as a sequence of interacting contributions whose meaning and function can change with context.

Areas of interest include:

- Dialogue acts and conversational functions, such as questions, answers, clarification, elaboration, disagreement, and topic transitions.
- Relationships between utterances, participants, referents, and conversational topics.
- Context carried forward from earlier turns.
- Changes in stance, interpretation, and apparent intent.
- Patterns of agreement, disagreement, ambiguity, repair, and conversational progression.
- Predictions about likely next conversational functions or structural developments.

The engine should distinguish what was explicitly said from what it infers. A declarative sentence is evidence about a speaker's position, not automatic proof of their underlying belief or intention. Sarcasm, strategic ambiguity, testing reactions, politeness, deception, and changing views can all complicate interpretation.

## Uncertainty and Competing Interpretations

CDE should not be designed around the assumption that every utterance has one immediately knowable meaning.

Where evidence is ambiguous, the engine should be able to preserve multiple competing hypotheses. Each hypothesis may carry a probability or confidence estimate, supporting evidence, and a record of how that estimate changes as new turns arrive.

This direction connects naturally with Bayesian reasoning:

1. Establish an initial hypothesis or prior.
2. Observe new conversational evidence.
3. Update the relative plausibility of competing interpretations.
4. Retain uncertainty when the evidence does not justify a single conclusion.
5. Revisit earlier interpretations when later context changes their meaning.

The system must avoid treating a numerical confidence score as certainty. It should also distinguish uncertainty about classification, uncertainty about the referent, uncertainty about speaker intent, and uncertainty about future conversational developments.

## Ontology: Preserve What Is Being Discussed

The ontology should distinguish the referents of conversation from the words or representations used to mention them.

The foundational referent classes are:

- **Entity:** an individual or collective referent that is, or has been, alive.
- **Item:** a nonliving referent, whether concrete or abstract.
- **Unknown:** a valid unresolved classification that can be revised when sufficient evidence becomes available.

A mention, photograph, document, or description is not automatically the thing it represents. For example, a photograph of a squirrel is an Item; the squirrel being depicted is a separate referent.

Relationships should represent connections among referents, participants, roles, and relevant properties. Time is an important dimension of relationships and conversational change, rather than a reason to make “Event” a primary peer category alongside Entity and Item.

The ontology should preserve uncertainty and provenance instead of silently turning tentative NLP output into established fact.

## Real-Time Operation

The intended system is ultimately a live, incrementally updated analyzer.

Real-time operation means that incoming conversational material can be processed as it arrives, with the system updating its state and predictions without requiring the entire conversation to be reprocessed as one batch.

Historical datasets can provide the initial experimental material. Where timestamps are absent, the engine must preserve turn order without inventing real-world timing. Simulated timing can be introduced for experiments, but it must remain distinguishable from observed timestamps.

## Prediction: Structure Before Sentence Generation

The initial prediction objective is to estimate the next conversational function or structural development, rather than generate an exact next sentence.

Potential predictions include:

- A response to a question.
- A request for clarification.
- An elaboration.
- A disagreement or challenge.
- A topic continuation or transition.
- A conversational repair or qualification.

Predictions should be evaluated against observed outcomes. The system should retain baselines and measure performance with appropriate metrics, potentially including accuracy, precision, recall, log loss, Brier score, and calibration. Chronological evaluation is important because future turns must not leak into the information used to predict earlier turns.

## Experimental Engineering and Resilience

CDE should be developed with the understanding that complex systems have interacting components and can fail in ways that are not fully anticipated.

Testing should therefore extend beyond ordinary successful operation. Controlled experiments can introduce latency, unavailable services, malformed responses, missing data, contradictory evidence, and ambiguous inputs.

The goal is to measure how failures and uncertainty propagate, whether data integrity is preserved, how the system recovers, and whether its predictions degrade gracefully.

Chaos engineering is relevant to the reliability of the software and its dependencies. Probabilistic inference and uncertainty-aware reasoning are related but distinct disciplines that address uncertainty in the system's interpretations. CDE can draw from both without treating them as interchangeable.

## Initial Research Dataset

**DailyDialog** is the initial conversational dataset. It contains everyday dialogue examples and annotations useful for studying dialogue acts and emotion.

It is a starting research corpus, not a complete representation of real-world social interaction. Its ordering can support sequential experiments, but timestamps should only be used if they are actually present and documented. Dataset limitations, licensing, annotation quality, and domain bias should be recorded as part of the research process.

## Guiding Engineering Principles

1. **Complexity should be represented when the problem requires it.** Do not flatten conversational phenomena merely to make the implementation convenient.
2. **Complexity must remain testable.** Rich models need explicit contracts, observable state, measurable behavior, and controlled experiments.
3. **Separate evidence from inference.** Preserve source utterances, extracted features, hypotheses, and predictions as distinct data.
4. **Represent uncertainty honestly.** Unknown is a legitimate state; confidence is not the same as truth.
5. **Preserve temporal order and provenance.** Record what was observed, when it was observed, and which conclusions were derived from it.
6. **Build incrementally without designing for triviality.** Early implementations may be small, but their interfaces should leave room for more sophisticated models and computation.
7. **Measure before claiming understanding.** Predictions and interpretations must be evaluated against evidence and meaningful baselines.
8. **Prefer replaceable components.** The NLP model, prediction strategy, storage implementation, and experimental methods should not be needlessly entangled.

## Long-Term Direction

CDE is intended to become a substantial analytical engineering system, not a lightweight productivity application or a simple chatbot.

Its ambition is to investigate conversational dynamics as a complex, evolving process: interpreting language in context, tracking relationships and state, maintaining competing hypotheses, predicting structural developments, and measuring the reliability of those conclusions.

The project should be ambitious in its research questions and disciplined in its engineering. Computational scale is justified when it produces measurable analytical value—not simply because complexity is desirable in itself.


---

## Development Update — Native Application & Database Foundation

### Current Changes

The project has established its initial native desktop application structure using **C++20, Qt 6 Widgets, and CMake**.

The initial application interface is organized into five primary panels:

- **Dialogue Stream** — dialogue ingestion and inspection.
- **Ontology and Referents** — semantic concepts and referent organization.
- **Relationships** — representation of relationships between conversational entities.
- **Prediction Engine** — future behavioral and conversational prediction.
- **Statistical Analysis** — statistical evaluation and visualization.

The application is being organized around an **MVCEP architecture**:

- **Model:** Domain objects and representations.
- **View:** Native Qt interface and presentation.
- **Controller:** Coordination of application workflows and user interactions.
- **Engine:** Computational analysis, inference, prediction, and evaluation.
- **Persistence:** Database connectivity, storage, retrieval, and repository operations.

### Database Foundation

SQLite has been selected as the initial database technology.

The project now includes a `DatabaseManager` foundation using Qt SQL (`QSqlDatabase`) and the SQLite driver (`QSQLITE`).

The initial database location is:

`data/databases/cde_research.sqlite`

The database directory is created automatically when the application initializes its database connection.

SQLite was selected because the application is initially intended to operate as a standalone, single-user research environment. It provides local persistence without requiring a separate database server.

### Planned SQLite Development

The following database capabilities are planned:

1. **Schema Design**
    - Dialogue records and utterance boundaries.
    - Dataset and source metadata.
    - Participant and conversational entity representations where supported by the source data.
    - Ontology and referent records.
    - Prediction results and evaluation records.

2. **Dataset Ingestion**
    - Import DailyDialog and future conversational datasets.
    - Preserve original source data and dataset partitions.
    - Maintain alignment between dialogues, utterances, and supplied annotations.
    - Track dataset provenance and import metadata.

3. **Repository Layer**
    - Introduce dedicated repositories for domain objects.
    - Separate SQL operations from the computational engine.
    - Support prepared statements, transactions, indexing, and efficient retrieval.

4. **Research and Evaluation Storage**
    - Persist statistical observations and experimental results.
    - Store prediction outputs independently of ground-truth annotations.
    - Support repeatable experiments and comparisons across model configurations.

5. **Performance and Scalability**
    - Use indexed queries and transactional bulk imports.
    - Retrieve large datasets incrementally rather than loading everything into memory.
    - Evaluate SQLite performance against actual research workloads before considering alternative database systems.

### Architectural Direction

The computational engine is intended to remain independent of Qt's presentation layer and the underlying database implementation.

This separation will allow the research engine to evolve independently and potentially become a reusable component of a larger Social Dynamics Engine.

The immediate development priority is establishing reliable data persistence before implementing dataset ingestion, analytical modules, and predictive capabilities.